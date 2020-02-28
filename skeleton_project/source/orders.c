#include <stdio.h>
#include <stdlib.h>
//#include "hardware.h"
#include "elevator.h"
#include "orders.h"

static int current_direction = HARDWARE_MOVEMENT_STOP;

extern int last_direction;
//change to elevator_order_array
int elevator_queue[4];

int get_current_direction(){
    return current_direction;
}

void set_current_direction(int direction){
    current_direction = direction;
}

int get_queue(int floor){
    return elevator_queue[floor];
}

void set_queue(int floor, int order){
    elevator_queue[floor] = order;
}


void set_order_up(){
    for (int i = 0; i < get_BUTTON_COUNT(); ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_UP)){
            if (elevator_queue[i] == BOTH_OR_INSIDE || elevator_queue[i] == DOWN){
                elevator_queue[i] = BOTH_OR_INSIDE;
            }
            else{
                elevator_queue[i] = UP;
            }
        }
    }
}

void set_order_down(){
    for (int i = 1; i < get_BUTTON_COUNT() + 1; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_DOWN)){
            if (elevator_queue[i] == BOTH_OR_INSIDE || elevator_queue[i] == UP){
                elevator_queue[i] = BOTH_OR_INSIDE;
            }
            else{
                elevator_queue[i] = DOWN;
            }
        }
    }
}

void set_order_inside(){
    for (int i = 0; i < get_BUTTON_COUNT() + 1; ++i){
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE)){
            //printf("Inside order read \n");
            elevator_queue[i] = BOTH_OR_INSIDE;
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
        if(elevator_queue[i] > 0){
            if(i > starting_point){
                return 1;
            }
        }
    }
    return 0;
}

int check_orders_below(int starting_point){
    for(int i = 0; i < get_FLOOR_COUNT(); ++i){
        if(elevator_queue[i] > 0){
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
        if(elevator_queue[i]){
            ++order_count;
        }
    }
    return order_count;
}

void update_current_direction(){
    if(!get_order_count()){
        current_direction = HARDWARE_MOVEMENT_STOP;
    } else if(check_orders_above(get_current_floor()) && !check_orders_below(get_current_floor())){
        current_direction = HARDWARE_MOVEMENT_UP;
    } else if(check_orders_below(get_current_floor()) && !check_orders_above(get_current_floor())){
        current_direction = HARDWARE_MOVEMENT_DOWN;
    } else if(current_direction == HARDWARE_MOVEMENT_STOP && !elevator_get_current_floor()){
        if (last_direction == HARDWARE_MOVEMENT_DOWN){
            if (check_orders_below(get_current_floor())){
                current_direction = HARDWARE_MOVEMENT_DOWN;
            }
            else if (check_orders_above(get_current_floor()-1)){
                current_direction = HARDWARE_MOVEMENT_UP;
            }
        } else if (last_direction == HARDWARE_MOVEMENT_UP){
            if (check_orders_below(get_current_floor()+1)){
                current_direction = HARDWARE_MOVEMENT_DOWN;
            } else if (check_orders_above(get_current_floor())){
                current_direction = HARDWARE_MOVEMENT_UP;
            }
        }
        
        /*
        if (check_orders_below(get_current_floor()+1) && !check_orders_above(get_current_floor())){ 
            current_direction = HARDWARE_MOVEMENT_DOWN;
        }
        else if (check_orders_above(get_current_floor()-1) && !check_orders_below(get_current_floor())){
            current_direction = HARDWARE_MOVEMENT_UP;
        }
        */
    }
}

int check_up_at_floor(){
    for(int i = 1; i < get_FLOOR_COUNT()+1; ++i){
        if(i == elevator_get_current_floor() && elevator_queue[i-1] == UP){
            return 1;
        }
    }
    return 0;
}

int check_down_at_floor(){
    for(int i = 1; i < get_FLOOR_COUNT()+1; ++i){
        if(i == elevator_get_current_floor() && elevator_queue[i-1] == DOWN){
            return 1;
        }
    }
    return 0;
}

int check_both_or_inside_at_floor(){
    for(int i = 1; i < get_FLOOR_COUNT()+1; ++i){
        if(i == elevator_get_current_floor() && elevator_queue[i-1] == BOTH_OR_INSIDE){
            return 1;
        }
    }
    return 0;
}

int check_arrival(){
    if(check_both_or_inside_at_floor()){
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
        elevator_queue[i] = 0;
    }
}

void print_all_orders(){
    for (int i = 0; i < get_FLOOR_COUNT(); ++i){
        printf("Floor %d, has index %d \n", i + 1, elevator_queue[i]);
    }
}
