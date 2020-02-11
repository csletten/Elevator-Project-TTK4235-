#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "fsm.h"
#include "orders.h"


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
                /* if (stopButton){
                    stop motor
                    orders_delete_all_orders()
                    enable stop light
                }else {
                    disable stop light
                    if (hardware_get_current_floor()){
                        set timer for 3 sec.
                        fsm_state_switch(DOOR);
                    }else{
                        fsm_state_switch(IDLE);
                    }
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
