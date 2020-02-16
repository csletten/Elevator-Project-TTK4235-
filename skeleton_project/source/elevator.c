#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevator.h"
#include "orders.h"
#include "timer.h"
#include "fsm.h"
#include "lights.h"

static int current_floor = 0;

int elevator_get_current_floor(){
    for(int i = 0; i < 4; i++){
        if(hardware_read_floor_sensor(i)){
            return i+1;
        }
    }
    return 0;
}

void elevator_set_current_floor(){
    if(elevator_get_current_floor()){
        current_floor = elevator_get_current_floor()-1;
    }
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

void travel_to_destination(int destination_floor){
    if(destination_floor > current_floor){   
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
    } else if(destination_floor < current_floor){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }else{
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    }
}

void run_elevator(){
    printf("Current floor: %d ", current_floor);
    set_lights(current_floor);
    elevator_startup();
    
    while (1)
    {
        printf("Current floor : %d \n ", current_floor);
        elevator_set_current_floor();
        set_lights(current_floor);
        travel_to_destination(3);
        //travel_to_destination(2);
        //travel_to_destination(1);
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