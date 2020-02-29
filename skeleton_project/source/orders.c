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

int get_queue(int floor){
    return elevator_order_array[floor];
}

void set_queue(int floor, int order){
    elevator_order_array[floor] = order;
}


void set_order_up(){
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

void set_order_down(){
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

void set_order_inside(){
    for (int i = 0; i < get_BUTTON_COUNT() + 1; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE)){
            elevator_order_array[i] = BOTH_OR_CAB;
        }
    }
}

void handle_orders(){
    set_order_up();
    set_order_down();
    set_order_inside();
}

int check_orders_above(int starting_point){
    for(int i = 0; i < get_FLOOR_COUNT(); ++i){
        if(elevator_order_array[i] > 0){
            if(i > starting_point){
                return 1;
            }
        }
    }
    return 0;
}

int check_orders_below(int starting_point){
    for(int i = 0; i < get_FLOOR_COUNT(); ++i){
        if(elevator_order_array[i] > 0){
            if(i < starting_point){
                return 1;
            }
        }
    }
    return 0;
}

int get_order_count(){
    int order_count = 0;
    for(int i = 0; i < get_FLOOR_COUNT(); ++i){
        if(elevator_order_array[i]){
            ++order_count;
        }
    }
    return order_count;
}

void update_current_direction(){
    if(!get_order_count()){
        current_direction = HARDWARE_MOVEMENT_STOP;
    } else if(current_direction == HARDWARE_MOVEMENT_STOP && !check_floor_number()){
        if (direction_from_last_floor == HARDWARE_MOVEMENT_DOWN){
            if (check_orders_below(get_current_floor())){
                current_direction = HARDWARE_MOVEMENT_DOWN;
            }
            else if (check_orders_above(get_current_floor()-1)){
                current_direction = HARDWARE_MOVEMENT_UP;
            }
        } else if (direction_from_last_floor == HARDWARE_MOVEMENT_UP){
            if (check_orders_below(get_current_floor()+1)){
                current_direction = HARDWARE_MOVEMENT_DOWN;
            } else if (check_orders_above(get_current_floor())){
                current_direction = HARDWARE_MOVEMENT_UP;
            }
        }
    } else if(check_orders_above(get_current_floor()) && !check_orders_below(get_current_floor())){
        current_direction = HARDWARE_MOVEMENT_UP;
    } else if(check_orders_below(get_current_floor()) && !check_orders_above(get_current_floor())){
        current_direction = HARDWARE_MOVEMENT_DOWN;
    }
}

int check_up_at_floor(){
    for(int i = 1; i < get_FLOOR_COUNT()+1; ++i){
        if(i == check_floor_number() && elevator_order_array[i-1] == UP){
            return 1;
        }
    }
    return 0;
}

int check_down_at_floor(){
    for(int i = 1; i < get_FLOOR_COUNT()+1; ++i){
        if(i == check_floor_number() && elevator_order_array[i-1] == DOWN){
            return 1;
        }
    }
    return 0;
}

int check_both_or_cab_at_floor(){
    for(int i = 1; i < get_FLOOR_COUNT()+1; ++i){
        if(i == check_floor_number() && elevator_order_array[i-1] == BOTH_OR_CAB){
            return 1;
        }
    }
    return 0;
}

int check_arrival(){
    if(check_both_or_cab_at_floor()){
        return 1;
    } else if(current_direction == HARDWARE_MOVEMENT_UP){
        if(check_up_at_floor()){
            return 1;
        } else if(check_down_at_floor() && !check_orders_above(get_current_floor())){
            return 1;
        }
    } else if(current_direction == HARDWARE_MOVEMENT_DOWN){
        if(check_down_at_floor()){
            return 1;
        } else if(check_up_at_floor() && !check_orders_below(get_current_floor())){
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