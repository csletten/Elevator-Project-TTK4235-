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

CurrentState state = IDLE;

int get_state(){
    return state;
}

void set_state(CurrentState new_state){
    state = new_state;
}

int get_current_floor(){
    return current_floor;
}

int get_FLOOR_COUNT(){
    return FLOOR_COUNT;
}

int get_BUTTON_COUNT(){
    return BUTTON_COUNT;
}

int elevator_get_current_floor()
{
    for (int i = 0; i < FLOOR_COUNT; i++)
    {
        if (hardware_read_floor_sensor(i))
        {
            return i + 1;
        }
    }
    return 0;
}

void elevator_set_current_floor()
{
    if (elevator_get_current_floor())
    {
        current_floor = elevator_get_current_floor() - 1;
    }
}

void elevator_startup()
{
    // Initalize hardware
    int error = hardware_init();
    if (error != 0)
    {
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    // Move to first floor
    while (elevator_get_current_floor() == 0)
    {
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void run_elevator()
{
    handle_lights();
    handle_orders();
    elevator_startup();
    int stopped_while_open;

    while (1)
    {
        handle_lights();
        handle_orders();
        elevator_set_current_floor();
        //printf("Current state: %d \n", state);
        //printf("UP: %d ", UP);
        //printf("Floor Count: %d \n", get_order_count());
        switch (state)
        {
        case IDLE:
            //printf("Current floor %d ", current_floor);
            //printf("ORDER BELOW %d ", check_orders_below());
             printf("Current direction PRE %d \n", get_current_direction());
            update_current_direction();
            printf("Current direction POST %d \n", get_current_direction());
            //printf("current dir %d ", get_current_direction());
            if((check_up_at_floor() || check_down_at_floor() || check_both_or_inside_at_floor()) && elevator_get_current_floor()){
                //print_all_orders();
                //printf("returning to door \n");
                state = DOOR;
            } else if(get_current_direction() != HARDWARE_MOVEMENT_STOP){
                hardware_command_movement(get_current_direction());
                //printf("RUNNING");
                state = RUNNING;
            }
            break;

        case RUNNING:
            handle_lights();
            handle_orders();
            elevator_set_current_floor();
            if(hardware_read_stop_signal()){
                state = EMERGENCY_STOP;
            }
            //printf("ORDER ABOVE %d \n", check_orders_above());
            //printf("CURRENT DIRECTION %d \n", current_direction);
            if(check_arrival()){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                state = DOOR;
            }
            break;

        case DOOR:
            hardware_command_door_open(1);
            //printf("Current floor %d \n ", current_floor+1);
            set_queue(current_floor, 0);
            //printf("PRE handling \n");
            //print_all_orders();
            handle_lights();
            handle_orders();
            //printf("POST handling \n");
            //print_all_orders();
            timer_start_timer(3000);
            //printf("DOOR \n");
            //printf("Up press %d \n", check_up_at_floor());
            //printf("DOWN press %d \n", check_down_at_floor());
            //printf("INSIDE press %d \n", check_both_or_inside_at_floor());
            while (!timer_check_expired()){
                handle_lights();
                handle_orders();
            }
            if (hardware_read_obstruction_signal())
            {
                state = OBSTRUCT;
            }else
            {
                hardware_command_door_open(0);
                update_current_direction();
                if(get_current_direction() == HARDWARE_MOVEMENT_STOP){
                    state = IDLE;
                } else{
                    hardware_command_movement(get_current_direction());
                    state = RUNNING;
                }

            }
            break;

        case EMERGENCY_STOP:
            set_current_direction(HARDWARE_MOVEMENT_STOP);
            hardware_command_movement(get_current_direction());
            clear_all_orders();
            stopped_while_open = 0;
            if (elevator_get_current_floor())
            {
                while (hardware_read_stop_signal())
                {
                    hardware_command_door_open(1);
                }
                timer_start_timer(3000);
                
                while (!timer_check_expired())
                {
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

        case OBSTRUCT:
            if (elevator_get_current_floor())
            {
                timer_start_timer(3000);
                while (!timer_check_expired())
                {
                    handle_lights();
                    handle_orders();
                }
                state = DOOR;
            }
            else
            {
                state = IDLE;
            }
            break;
        }
    }
}