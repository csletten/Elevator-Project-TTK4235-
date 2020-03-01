#include <stdio.h>
#include <stdlib.h>
//#include "hardware.h"
#include "elevator.h"
#include "orders.h"

static int current_direction = HARDWARE_MOVEMENT_STOP;

extern int direction_from_last_floor;

int elevator_order_array[4];

int get_current_direction(){
    return current_direction;
}

void set_current_direction(int direction){
    current_direction = direction;
}

int get_order_at_floor(int floor){
    return elevator_order_array[floor];
}

void set_order_at_floor(int floor, int order){
    elevator_order_array[floor] = order;
}


void orders_set_order_up(){
    for (int i = 0; i < get_BUTTON_COUNT(); ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_UP)){
            if (elevator_order_array[i] == BOTH_OR_CAB || elevator_order_array[i] == DOWN){
                elevator_order_array[i] = BOTH_OR_CAB;
            }
            else{
                elevator_order_array[i] = UP;
            }
        }
    }
}

void orders_set_order_down(){
    for (int i = 1; i < get_BUTTON_COUNT() + 1; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_DOWN)){
            if (elevator_order_array[i] == BOTH_OR_CAB || elevator_order_array[i] == UP){
                elevator_order_array[i] = BOTH_OR_CAB;
            }
            else{
                elevator_order_array[i] = DOWN;
            }
        }
    }
}

void orders_set_order_inside(){
    for (int i = 0; i < get_BUTTON_COUNT() + 1; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE)){
            elevator_order_array[i] = BOTH_OR_CAB;
        }
    }
}

//update this name to fexample orders_set_all orders()
void handle_orders(){
    orders_set_order_up();
    orders_set_order_down();
    orders_set_order_inside();
}

int orders_check_orders_above(int starting_point){
    for(int i = 0; i < get_FLOOR_COUNT(); ++i){
        if(elevator_order_array[i] > 0){
            if(i > starting_point){
                return 1;
            }
        }
    }
    return 0;
}

int orders_check_orders_below(int starting_point){
    for(int i = 0; i < get_FLOOR_COUNT(); ++i){
        if(elevator_order_array[i] > 0){
            if(i < starting_point){
                return 1;
            }
        }
    }
    return 0;
}

int orders_get_order_count(){
    int order_count = 0;
    for(int i = 0; i < get_FLOOR_COUNT(); ++i){
        if(elevator_order_array[i]){
            ++order_count;
        }
    }
    return order_count;
}

//change name to orders_update_direction()?
void orders_update_current_direction(){
    if(!orders_get_order_count()){
        current_direction = HARDWARE_MOVEMENT_STOP;
    } else if(current_direction == HARDWARE_MOVEMENT_STOP && !check_floor_number()){
        if (direction_from_last_floor == HARDWARE_MOVEMENT_DOWN){
            if (orders_check_orders_below(elevator_get_current_floor())){
                current_direction = HARDWARE_MOVEMENT_DOWN;
            }
            else if (orders_check_orders_above(elevator_get_current_floor()-1)){
                current_direction = HARDWARE_MOVEMENT_UP;
            }
        } else if (direction_from_last_floor == HARDWARE_MOVEMENT_UP){
            if (orders_check_orders_below(elevator_get_current_floor()+1)){
                current_direction = HARDWARE_MOVEMENT_DOWN;
            } else if (orders_check_orders_above(elevator_get_current_floor())){
                current_direction = HARDWARE_MOVEMENT_UP;
            }
        }
    } else if(orders_check_orders_above(elevator_get_current_floor()) && !orders_check_orders_below(elevator_get_current_floor())){
        current_direction = HARDWARE_MOVEMENT_UP;
    } else if(orders_check_orders_below(elevator_get_current_floor()) && !orders_check_orders_above(elevator_get_current_floor())){
        current_direction = HARDWARE_MOVEMENT_DOWN;
    }
}

int orders_check_up_at_floor(){
    for(int i = 1; i < get_FLOOR_COUNT()+1; ++i){
        if(i == check_floor_number() && elevator_order_array[i-1] == UP){
            return 1;
        }
    }
    return 0;
}

int orders_check_down_at_floor(){
    for(int i = 1; i < get_FLOOR_COUNT()+1; ++i){
        if(i == check_floor_number() && elevator_order_array[i-1] == DOWN){
            return 1;
        }
    }
    return 0;
}

int orders_check_both_or_cab_at_floor(){
    for(int i = 1; i < get_FLOOR_COUNT()+1; ++i){
        if(i == check_floor_number() && elevator_order_array[i-1] == BOTH_OR_CAB){
            return 1;
        }
    }
    return 0;
}

int orders_check_arrival(){
    if(orders_check_both_or_cab_at_floor()){
        return 1;
    } else if(current_direction == HARDWARE_MOVEMENT_UP){
        if(orders_check_up_at_floor()){
            return 1;
        } else if(orders_check_down_at_floor() && !orders_check_orders_above(elevator_get_current_floor())){
            return 1;
        }
    } else if(current_direction == HARDWARE_MOVEMENT_DOWN){
        if(orders_check_down_at_floor()){
            return 1;
        } else if(orders_check_up_at_floor() && !orders_check_orders_below(elevator_get_current_floor())){
            return 1;
        }
    }
    return 0;
}

void clear_all_orders(){
    for (int i = 0; i < get_FLOOR_COUNT(); ++i){
        elevator_order_array[i] = 0;
    }
}

void print_all_orders(){
    for (int i = 0; i < get_FLOOR_COUNT(); ++i){
        printf("Floor %d, has index %d \n", i + 1, elevator_order_array[i]);
    }
}

int bool_order_at_floor(int floor){
    if(elevator_order_array[floor]){
        return 1;
    }
    return 0;
}