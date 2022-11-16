#include <stdio.h>
#include <stdlib.h>
#include "elevator.h"
#include "signal.h"

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    signal(SIGINT, sigint_handler);
    elevator_run_elevator();
    return 0;
}
