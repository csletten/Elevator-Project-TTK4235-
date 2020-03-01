#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevator.h"
#include "orders.h"
#include "lights.h"
#include "timer.h"

int FLOOR_COUNT = 4;
int BUTTON_COUNT = 3;

static int current_floor = 0;
int direction_from_last_floor;

CurrentState state = IDLE;

int elevator_get_state(){
    return state;
}

void elevator_set_state(CurrentState new_state){
    state = new_state;
}

int elevator_get_current_floor(){
    return current_floor;
}

int elevator_get_FLOOR_COUNT(){
    return FLOOR_COUNT;
}

int elevator_get_BUTTON_COUNT(){
    return BUTTON_COUNT;
}

int elevator_one_indexed_floor_number(){
    for (int i = 0; i < FLOOR_COUNT; i++){
        if (hardware_read_floor_sensor(i)){
            return i + 1;
        }
    }
    return 0;
}

void elevator_update_current_floor(){
    if (elevator_one_indexed_floor_number()){
        current_floor = elevator_one_indexed_floor_number() - 1;
        direction_from_last_floor = orders_get_current_direction();
    }
}

void elevator_startup(){
    int error = hardware_init();
    if (error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    while (elevator_one_indexed_floor_number() == 0){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void elevator_run_elevator(){
    lights_set_and_clear_lights();
    orders_set_all_orders();
    elevator_startup();
    int stopped_while_open;
    int repeated_open;
    int stopped_while_obstructed;

    while (1){
        elevator_update_current_floor();
        lights_set_and_clear_lights();
        orders_set_all_orders();

        switch (state)
        {
        case IDLE:
            orders_update_current_direction();
            if(orders_bool_order_at_floor(current_floor) && elevator_one_indexed_floor_number()){
                state = FLOOR;
            } else if(orders_get_current_direction() != HARDWARE_MOVEMENT_STOP){
                hardware_command_movement(orders_get_current_direction());
                if(elevator_one_indexed_floor_number()){
                    direction_from_last_floor = orders_get_current_direction();
                }
                state = RUNNING;
            }
            break;

        case RUNNING:
            if(hardware_read_stop_signal()){
                state = EMERGENCY_STOP;
            } else if(orders_check_arrival()){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                state = FLOOR;
            }
            break;

        case FLOOR:
            hardware_command_door_open(1);
            repeated_open = 0;
            orders_set_order_at_floor(current_floor, 0);
            timer_start_timer(3000);

            while (!timer_check_expired()){
                orders_set_order_at_floor(current_floor, 0);
                lights_set_and_clear_lights();
                orders_set_all_orders();
                if(hardware_read_stop_signal()){
                    state = EMERGENCY_STOP;
                    break;
                } else if(orders_bool_order_at_floor(current_floor)){
                    state = FLOOR;
                    repeated_open = 1;
                    break;
                }
            }
            if (hardware_read_obstruction_signal()){
                state = OBSTRUCTED;
            } else if(!repeated_open){
                hardware_command_door_open(0);
                orders_update_current_direction();
                if(orders_get_current_direction() == HARDWARE_MOVEMENT_STOP){
                    state = IDLE;
                } else{
                    hardware_command_movement(orders_get_current_direction());
                    direction_from_last_floor = orders_get_current_direction();
                    state = RUNNING;
                }
            }
            break;

        case EMERGENCY_STOP:
            orders_set_current_direction(HARDWARE_MOVEMENT_STOP);
            hardware_command_movement(orders_get_current_direction());
            orders_clear_all_orders();
            lights_set_and_clear_lights();
            stopped_while_open = 0;
            if(hardware_read_obstruction_signal()){
                state = OBSTRUCTED;
                break;
            }
            if (elevator_one_indexed_floor_number()){
                while (hardware_read_stop_signal()){
                    hardware_command_door_open(1);
                }
                timer_start_timer(3000);
                
                while (!timer_check_expired()){
                    lights_set_and_clear_lights();
                    orders_set_all_orders();
                    hardware_command_stop_light(hardware_read_stop_signal());
                    if(hardware_read_stop_signal()){
                        stopped_while_open = 1;
                        break;
                    }    
                }
                if(!stopped_while_open){
                    hardware_command_door_open(0);
                }
                
            }
            if(!stopped_while_open){
                hardware_command_stop_light(0);
                state = IDLE;
            }
            break;

        case OBSTRUCTED:
            stopped_while_obstructed = 0;
            while (elevator_one_indexed_floor_number() && hardware_read_obstruction_signal()){
                orders_set_order_at_floor(current_floor, 0);
                lights_set_and_clear_lights();
                orders_set_all_orders();
                if(hardware_read_stop_signal()){
                    stopped_while_obstructed = 1;
                    state = EMERGENCY_STOP;
                    break;
                }
            }
            if(!stopped_while_obstructed){
                state = FLOOR;
            }
            break;
        }
    }
}