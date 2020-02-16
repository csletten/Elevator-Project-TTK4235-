#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevator.h"
#include "orders.h"
#include "timer.h"
#include "fsm.h"


int FLOOR_COUNT = 4;
int BUTTON_COUNT = 3;

int elevator_get_current_floor(){
    for(int i = 0; i < FLOOR_COUNT; i++){
        if(hardware_read_floor_sensor(i)){
            return i+1;
        }
    }
    return 0;
}

void set_order_lights_up() {
    for (int i = 0; i < BUTTON_COUNT; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_UP)) {
            hardware_command_order_light(i, HARDWARE_ORDER_UP, 1);
        }
    }
}

void set_order_lights_down() {
    for (int i = 1; i < BUTTON_COUNT+1; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_DOWN)) {
            hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 1);
        }
    }
}

void set_order_lights_inside(){
    for(int i = 0; i < BUTTON_COUNT + 1; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE)) {
            hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 1);
        }
    }
    //hardware_command_order_light(3, HARDWARE_ORDER_INSIDE, 1);
}

void set_stop_light(){
    if(hardware_read_stop_signal()){
        hardware_command_stop_light(1);
    }
}

void set_lights(){
    set_order_lights_up();
    set_order_lights_down();
    set_order_lights_inside();
    set_stop_light();
}

void elevator_startup(){
     // Initalize hardware
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    // Move to first floor
    while(elevator_get_current_floor() != 1){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);

}

void travel_to_destination(int floor){
    while(elevator_get_current_floor() != floor){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void run_elevator(){
    elevator_startup();

    //travel_to_destination(2);
    
    while (1)
    {
        set_lights();
    }
    // CurrentState state = IDLE;

    //int order_array[4];
    
    /*
    while(1){
        set_correct_light_at_floor();
        //hardware_handle_stop_light();
        switch(state){
            case IDLE:
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_door_open(0);
                orders_update_order_array();
                for(int i = 0; i < order_array.size(); ++i){
                    if(!order_array[i]){
                        if(hardware_get_current_floor() == i+1){
                            fsm_state_switch(DOOR);
                        } else{
                            fsm_state_switch(RUNNING);
                        } 
                    }hardware_get_current_floor
                }
                break;
                
            
            case RUNNING:
                // orders_update_order_array();
                break;

            case DOOR:
                // orders_update_order_array();
                break;s.

            case EMERGENCY_STOP:
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                orders_delete_all_orders(order_array);
                hardware_handle_stop_light();
                if(hardware_get_current_floor()){
                    while(hardware_read_stop_signal()){
                        hardware_command_door_open(1);
                        hardware_handle_stop_light();
                    }
                    timer_start_timer(3000);
                    while(!timer_check_expired){
                    }
                    hardware_command_door_open(0);
                    fsm_state_switch(IDLE);
                } else{
                    fsm_state_switch(IDLE);HARDWARE_MOVEMENT_UP
                }
                
                break;

            case OBSTRUCT:
                // orders_update_order_array();
                if (hardware_get_current_floor()){
                        set timer for 3 sec.
                        fsm_state_switch(DOOR);
                    }else{
                        fsm_state_switch(IDLE);
                    }
                
                break;

        }
        
    }*/
}