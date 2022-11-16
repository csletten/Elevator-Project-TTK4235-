#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static clock_t start;

static int duration;

void timer_start_timer(int msec){
    start = clock();
    duration = msec;
}

int timer_check_expired(){
    int difference_int;
    clock_t difference = clock() - start;
    difference_int = difference * 1000 / CLOCKS_PER_SEC;
    if (difference_int < duration){
        return 0;
    } else{
        return 1;
    }
}

void timer_print_current_time(){
    clock_t current_time = clock();
    printf("%ld \n", current_time);
}

void timer_test_timer(){
    timer_start_timer(5000);
    while(!timer_check_expired()){
        timer_print_current_time();
    }
    printf("TIMER STOPPED!");
}