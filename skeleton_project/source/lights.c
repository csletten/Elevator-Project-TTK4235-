#include <stdio.h>
#include <stdlib.h>
//#include "hardware.h"
#include "elevator.h"
#include "lights.h"
#include "orders.h"

void lights_set_order_lights_up(){
    for (int i = 0; i < elevator_get_BUTTON_COUNT(); ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_UP)){
            hardware_command_order_light(i, HARDWARE_ORDER_UP, 1);
        }
    }
}

void lights_clear_order_lights_up(){
    for (int i = 0; i < elevator_get_BUTTON_COUNT(); ++i){
        if (orders_get_order_at_floor(i) == 0 || orders_get_order_at_floor(i) == 2){
            hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
        }
    }
}

void lights_set_order_lights_down(){
    for (int i = 1; i < elevator_get_BUTTON_COUNT() + 1; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_DOWN)){
            hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 1);
        }
    }
}

void lights_clear_order_lights_down(){
    for (int i = 1; i < elevator_get_BUTTON_COUNT() + 1; ++i){
        if (orders_get_order_at_floor(i) == 0 || orders_get_order_at_floor(i) == 1){
            hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
        }
    }
}

void lights_set_order_lights_inside(){
    for (int i = 0; i < elevator_get_BUTTON_COUNT() + 1; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE)){
            hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 1);
        }
    }
}

void lights_clear_order_lights_inside(){
    for (int i = 0; i < elevator_get_BUTTON_COUNT() + 1; ++i){
        if (orders_get_order_at_floor(i) != 3){
            hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
        }
    }
}

void lights_set_stop_light(){
    if (hardware_read_stop_signal()){
        elevator_set_state(EMERGENCY_STOP);
    }
    hardware_command_stop_light(hardware_read_stop_signal());
}

void lights_set_floor_lights(){
    //printf("Current floor: %d ", current_floor);
    hardware_command_floor_indicator_on(elevator_get_current_floor());
}

void lights_set_and_clear_lights(){
    lights_set_order_lights_up();
    lights_clear_order_lights_up();
    lights_set_order_lights_down();
    lights_clear_order_lights_down();
    lights_set_order_lights_inside();
    lights_clear_order_lights_inside();
    lights_set_stop_light();
    lights_set_floor_lights();
}