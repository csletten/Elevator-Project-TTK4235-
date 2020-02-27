#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevator.h"
#include "timer.h"

int FLOOR_COUNT = 4;
int BUTTON_COUNT = 3;

static int current_floor = 0;
static int current_direction = HARDWARE_MOVEMENT_STOP;

int elevator_queue[4];

CurrentState state = IDLE;

int elevator_get_current_floor()
{
    for (int i = 0; i < FLOOR_COUNT; i++)
    {
        if (hardware_read_floor_sensor(i))
        {
            return i + 1;
        }
    }
    return 0;
}

void elevator_set_current_floor()
{
    if (elevator_get_current_floor())
    {
        current_floor = elevator_get_current_floor() - 1;
    }
}

void print_elevator_queue()
{
    for (int i = 0; i < FLOOR_COUNT; ++i)
    {
        printf("Floor %d, has index %d \n", i + 1, elevator_queue[i]);
    }
}

void order_buttons_up()
{
    for (int i = 0; i < BUTTON_COUNT; ++i)
    {
        if (hardware_read_order(i, HARDWARE_ORDER_UP))
        {
            hardware_command_order_light(i, HARDWARE_ORDER_UP, 1);
            if (elevator_queue[i] == BOTH_OR_INSIDE || elevator_queue[i] == DOWN)
            {
                elevator_queue[i] = BOTH_OR_INSIDE;
            }
            else
            {
                elevator_queue[i] = UP;
            }
        }
    }
}

void clear_order_buttons_up()
{
    for (int i = 0; i < BUTTON_COUNT; ++i)
    {
        if (elevator_queue[i] == 0 || elevator_queue[i] == 2)
        {
            hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
        }
    }
}

void order_buttons_down()
{
    for (int i = 1; i < BUTTON_COUNT + 1; ++i)
    {
        if (hardware_read_order(i, HARDWARE_ORDER_DOWN))
        {
            hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 1);
            if (elevator_queue[i] == BOTH_OR_INSIDE || elevator_queue[i] == UP)
            {
                elevator_queue[i] = BOTH_OR_INSIDE;
            }
            else
            {
                elevator_queue[i] = DOWN;
            }
        }
    }
}

void clear_order_buttons_down()
{
    for (int i = 1; i < BUTTON_COUNT + 1; ++i)
    {
        if (elevator_queue[i] == 0 || elevator_queue[i] == 1)
        {
            hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
        }
    }
}

void order_buttons_inside()
{
    for (int i = 0; i < BUTTON_COUNT + 1; ++i)
    {
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE))
        {
            hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 1);
            elevator_queue[i] = BOTH_OR_INSIDE;
            //printf("Inside button on floor %d pressed ", i);
        }
    }
}

void clear_order_buttons_inside()
{
    for (int i = 0; i < BUTTON_COUNT + 1; ++i)
    {
        if (elevator_queue[i] != 3)
        {
            hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
        }
    }
}

void stop_button()
{
    if (hardware_read_stop_signal())
    {
        state = EMERGENCY_STOP;
    }
    hardware_command_stop_light(hardware_read_stop_signal());
}

void floor_lights()
{
    //printf("Current floor: %d ", current_floor);
    hardware_command_floor_indicator_on(current_floor);
}

void handle_buttons()
{
    order_buttons_up();
    clear_order_buttons_up();
    order_buttons_down();
    clear_order_buttons_down();
    order_buttons_inside();
    clear_order_buttons_inside();
    stop_button();
    floor_lights();
}

void clear_all_orders()
{
    for (int i = 0; i < FLOOR_COUNT; ++i)
    {
        elevator_queue[i] = 0;
    }
}


int check_queue_above(int starting_point){
    for(int i = 0; i < FLOOR_COUNT; ++i){
        if(elevator_queue[i] > 0){
            if(i > starting_point){
                return 1;
            }
        }
    }
    return 0;
}

int check_queue_below(int starting_point){
    for(int i = 0; i < FLOOR_COUNT; ++i){
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
    for(int i = 0; i < FLOOR_COUNT; ++i){
        if(elevator_queue[i]){
            ++order_count;
        }
    }
    return order_count;
}

void update_current_direction(){
    if(!get_order_count()){
        current_direction = HARDWARE_MOVEMENT_STOP;
    } else if(check_queue_above(current_floor) && !check_queue_below(current_floor)){
        current_direction = HARDWARE_MOVEMENT_UP;
    } else if(check_queue_below(current_floor) && !check_queue_above(current_floor)){
        current_direction = HARDWARE_MOVEMENT_DOWN;
    } else if(current_direction == HARDWARE_MOVEMENT_STOP && !elevator_get_current_floor()){
        if (check_queue_below(current_floor+1) && !check_queue_above(current_floor)){
            current_direction = HARDWARE_MOVEMENT_DOWN;
        } 
        else if (check_queue_above(current_floor-1) && !check_queue_below(current_floor)){
            current_direction = HARDWARE_MOVEMENT_UP;
        }
    }
}
/*
void running_from_floor(){
    if(elevator_get_current_floor()){
        if(check_queue_above()){
            current_direction = HARDWARE_MOVEMENT_UP;
            hardware_command_movement(current_direction);
        }
        if(check_queue_below()){
            current_direction = HARDWARE_MOVEMENT_DOWN;
            hardware_command_movement(current_direction);
        }
        if(!check_queue_above() && !check_queue_below()){
            current_direction = HARDWARE_MOVEMENT_STOP;
            hardware_command_movement(current_direction);
        }
    }
}


void running_between_floors(){
    if(!elevator_get_current_floor()){
        if(check_queue_above()){
            current_direction = HARDWARE_MOVEMENT_UP;
            hardware_command_movement(current_direction);
        }
        if(check_queue_below()){
            current_direction = HARDWARE_MOVEMENT_DOWN;
            hardware_command_movement(current_direction);
        }
        if(elevator_queue[current_floor +1]){
            current_direction = HARDWARE_MOVEMENT_DOWN;
            hardware_command_movement(current_direction);
        }
    }
}
*/


int check_up_at_floor(){
    for(int i = 1; i < FLOOR_COUNT+1; ++i){
        if(i == elevator_get_current_floor() && elevator_queue[i-1] == UP){
            return 1;
        }
    }
    return 0;
}

int check_down_at_floor(){
    for(int i = 1; i < FLOOR_COUNT+1; ++i){
        if(i == elevator_get_current_floor() && elevator_queue[i-1] == DOWN){
            return 1;
        }
    }
    return 0;
}

int check_both_or_inside_at_floor(){
    for(int i = 1; i < FLOOR_COUNT+1; ++i){
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
        } else if(check_down_at_floor() && !check_queue_above(current_floor)){
            return 1;
        }
    } else if(current_direction == HARDWARE_MOVEMENT_DOWN){
        if(check_down_at_floor()){
            return 1;
        } else if(check_up_at_floor() && !check_queue_below(current_floor)){
            return 1;
        }
    }
    return 0;
}

void elevator_startup()
{
    // Initalize hardware
    int error = hardware_init();
    if (error != 0)
    {
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    // Move to first floor
    while (elevator_get_current_floor() != 1)
    {
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void run_elevator()
{
    handle_buttons();
    elevator_startup();
    int stopped_while_open;

    while (1)
    {
        handle_buttons();
        elevator_set_current_floor();
        //printf("Current state: %d \n", state);
        //printf("UP: %d ", UP);
        printf("Floor Count: %d \n", get_order_count());
        switch (state)
        {
        case IDLE:
            //printf("Current floor %d ", current_floor);
            //printf("ORDER BELOW %d ", check_queue_below());
            update_current_direction();
            printf("current dir %d ", current_direction);
            if((check_up_at_floor() || check_down_at_floor() || check_both_or_inside_at_floor()) && elevator_get_current_floor()){
                state = DOOR;
            } else if(current_direction != HARDWARE_MOVEMENT_STOP){
                hardware_command_movement(current_direction);
                printf("RUNNING");
                state = RUNNING;
            }
            break;

        case RUNNING:
            handle_buttons();
            elevator_set_current_floor();
            if(hardware_read_stop_signal()){
                state = EMERGENCY_STOP;
            }
            //printf("ORDER ABOVE %d \n", check_queue_above());
            //printf("CURRENT DIRECTION %d \n", current_direction);
            if(check_arrival()){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                state = DOOR;
            }
            break;

        case DOOR:
            hardware_command_door_open(1);
            elevator_queue[current_floor] = 0;
            handle_buttons();
            timer_start_timer(3000);

            while (!timer_check_expired())
            {
                handle_buttons();
            }
            if (hardware_read_obstruction_signal())
            {
                state = OBSTRUCT;
            }else
            {
                hardware_command_door_open(0);
                update_current_direction();
                if(current_direction == HARDWARE_MOVEMENT_STOP){
                    state = IDLE;
                } else{
                    hardware_command_movement(current_direction);
                    state = RUNNING;
                }

            }
            break;
        case EMERGENCY_STOP:
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            clear_all_orders();
            stopped_while_open = 0;
            if (elevator_get_current_floor())
            {
                while (hardware_read_stop_signal())
                {
                    hardware_command_door_open(1);
                }
                timer_start_timer(3000);
                
                while (!timer_check_expired())
                {
                    hardware_command_stop_light(hardware_read_stop_signal());
                    if(hardware_read_stop_signal()){
                        stopped_while_open = 1;
                        break;
                    }
                       
                }
                if(!stopped_while_open){
                    hardware_command_door_open(0);
                }
                
            }
            if(!stopped_while_open){
                hardware_command_stop_light(0);
                state = IDLE;
            }
            break;

        case OBSTRUCT:
            if (elevator_get_current_floor())
            {
                timer_start_timer(3000);
                while (!timer_check_expired())
                {
                    handle_buttons();
                }
                state = DOOR;
            }
            else
            {
                state = IDLE;
            }
            break;
        }
    }
}