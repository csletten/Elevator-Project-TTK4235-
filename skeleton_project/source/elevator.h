
/**
 * @brief Gets the current floor. 
 *
 * @return Return current floor. If no current floor return 0.
 */

int elevator_get_current_floor();

void set_order_lights_up();

void set_order_lights_down();

void set_order_lights_inside();

void set_stop_light();

void set_lights();

void elevator_startup();

void travel_to_destination(int floor);

void run_elevator();

