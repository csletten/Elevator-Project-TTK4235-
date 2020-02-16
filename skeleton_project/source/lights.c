#include "lights.h"
#include "elevator.h"
#include "hardware.h"


int FLOOR_COUNT = 4;
int BUTTON_COUNT = 3;

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

void set_floor_lights(int current_floor){
    //printf("Current floor: %d ", current_floor);
    hardware_command_floor_indicator_on(current_floor);
}

void set_lights(int current_floor){
    set_order_lights_up();
    set_order_lights_down();
    set_order_lights_inside();
    set_stop_light();
    set_floor_lights(current_floor);
}