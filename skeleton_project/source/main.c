#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "fsm.h"
#include "orders.h"
#include <time.h>


int main(){

    // Initalize hardware
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    CurrentState state = IDLE;

    int order_array[4];

    while(1){
        //hardware_handle_stop_light();
        switch(state){
            case IDLE:
                // orders_update_order_array();
                // for loop check order_array
                // if not zero -> switch state
                break;
            
            case RUNNING:
                // orders_update_order_array();
                break;

            case DOOR:
                // orders_update_order_array();
                break;

            case EMERGENCY_STOP:
                /*
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                orders_delete_all_orders(order_array);
                hardware_handle_stop_light();
                if(hardware_get_current_floor()){
                    while(hardware_read_stop_signal()){
                        hardware_command_door_open(1);
                        hardware_handle_stop_light();
                    }
                    int msec = 0, trigger = 3000;
                    clock_t before = clock();
                    while ( msec < trigger ){
                        clock_t difference = clock() - before;
                        msec = difference * 1000 / CLOCKS_PER_SEC;
                        hardware_command_door_open(1);
                    }
                    hardware_command_door_open(0);
                    fsm_state_switch(IDLE);
                } else{
                    fsm_state_switch(IDLE);
                }
                */
                break;

            case OBSTRUCT:
                // orders_update_order_array();
                /*
                if (hardware_get_current_floor()){
                        set timer for 3 sec.
                        fsm_state_switch(DOOR);
                    }else{
                        fsm_state_switch(IDLE);
                    }
                */
                break;

        }
        
    }
}
