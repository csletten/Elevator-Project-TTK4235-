typedef enum {
    IDLE,
    RUNNING,
    EMERGENCY_STOP,
    DOOR,
    OBSTRUCT
} CurrentState;

/**
 * @brief Gets the current floor. 
 *
 * @return Return current floor. If no current floor return 0.
 */

int elevator_get_current_floor();

void elevator_set_current_floor();

void order_buttons_up();

void order_buttons_down();

void order_buttons_inside();

void stop_button();

void floor_lights();

void buttons();

void elevator_startup();

void travel_to_destination(int destination_floor);

void run_elevator();

