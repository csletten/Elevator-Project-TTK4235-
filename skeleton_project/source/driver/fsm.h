#include "hardware.h"
#include "channels.h"
#include "io.h"

#include <stdlib.h>

typedef enum {
    IDLE,
    RUNNING,
    EMERGENCY_STOP,
    DOOR,
    OBSTRUCT
} CurrentState;

void fsm_state_switch(CurrentState state);