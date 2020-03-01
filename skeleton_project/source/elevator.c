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

int get_FLOOR_COUNT(){
    return FLOOR_COUNT;
}

int get_BUTTON_COUNT(){
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
        direction_from_last_floor = get_current_direction();
    }
}

void elevator_startup(){
    // Initalize hardware
    int error = hardware_init();
    if (error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    // Move down until a floor is reached
    while (elevator_one_indexed_floor_number() == 0){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void run_elevator(){
    handle_lights();
    handle_orders();
    elevator_startup();
    int stopped_while_open;
    int repeated_open;

    while (1){
        handle_lights();
        handle_orders();
        elevator_update_current_floor();
        switch (state)
        {
        case IDLE:
            orders_update_current_direction();
            if(bool_order_at_floor(current_floor) && elevator_one_indexed_floor_number()){
                state = FLOOR;
            } else if(get_current_direction() != HARDWARE_MOVEMENT_STOP){
                hardware_command_movement(get_current_direction());
                if(elevator_one_indexed_floor_number()){
                    direction_from_last_floor = get_current_direction();
                }
                state = RUNNING;
            }
            break;

        case RUNNING:
            handle_lights();
            handle_orders();
            elevator_update_current_floor();
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
            timer_start_timer(3000);

            while (!timer_check_expired()){
                set_order_at_floor(current_floor, 0);
                handle_lights();
                handle_orders();
                if(hardware_read_stop_signal()){
                    state = EMERGENCY_STOP;
                    break;
                } else if(bool_order_at_floor(current_floor)){
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
                if(get_current_direction() == HARDWARE_MOVEMENT_STOP){
                    state = IDLE;
                } else{
                    hardware_command_movement(get_current_direction());
                    direction_from_last_floor = get_current_direction();
                    state = RUNNING;
                }
            }
            break;

        case EMERGENCY_STOP:
            set_current_direction(HARDWARE_MOVEMENT_STOP);
            hardware_command_movement(get_current_direction());
            clear_all_orders();
            handle_lights();
            stopped_while_open = 0;
            if (elevator_one_indexed_floor_number()){
                while (hardware_read_stop_signal()){
                    hardware_command_door_open(1);
                }
                timer_start_timer(3000);
                
                while (!timer_check_expired()){
                    handle_lights();
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
            if (elevator_one_indexed_floor_number()){
                timer_start_timer(3000);
                while (!timer_check_expired()){
                    handle_lights();
                    handle_orders();
                }
                state = FLOOR;
            } else{
                state = IDLE;
            }
            break;
        }
    }
}