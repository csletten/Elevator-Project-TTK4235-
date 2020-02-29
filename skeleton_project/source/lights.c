#include <stdio.h>
#include <stdlib.h>
//#include "hardware.h"
#include "elevator.h"
#include "lights.h"
#include "orders.h"

void set_order_lights_up(){
    for (int i = 0; i < get_BUTTON_COUNT(); ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_UP)){
            hardware_command_order_light(i, HARDWARE_ORDER_UP, 1);
        }
    }
}

void clear_order_lights_up(){
    for (int i = 0; i < get_BUTTON_COUNT(); ++i){
        if (get_order_at_floor(i) == 0 || get_order_at_floor(i) == 2){
            hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
        }
    }
}

void set_order_lights_down(){
    for (int i = 1; i < get_BUTTON_COUNT() + 1; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_DOWN)){
            hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 1);
        }
    }
}

void clear_order_lights_down(){
    for (int i = 1; i < get_BUTTON_COUNT() + 1; ++i){
        if (get_order_at_floor(i) == 0 || get_order_at_floor(i) == 1){
            hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
        }
    }
}

void set_order_lights_inside(){
    for (int i = 0; i < get_BUTTON_COUNT() + 1; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE)){
            hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 1);
        }
    }
}

void clear_order_lights_inside(){
    for (int i = 0; i < get_BUTTON_COUNT() + 1; ++i){
        if (get_order_at_floor(i) != 3){
            hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
        }
    }
}

void set_stop_light(){
    if (hardware_read_stop_signal()){
        set_state(EMERGENCY_STOP);
    }
    hardware_command_stop_light(hardware_read_stop_signal());
}

void set_floor_lights(){
    //printf("Current floor: %d ", current_floor);
    hardware_command_floor_indicator_on(get_current_floor());
}

void handle_lights(){
    set_order_lights_up();
    clear_order_lights_up();
    set_order_lights_down();
    clear_order_lights_down();
    set_order_lights_inside();
    clear_order_lights_inside();
    set_stop_light();
    set_floor_lights();
}