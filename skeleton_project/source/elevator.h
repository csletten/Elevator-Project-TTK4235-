
/**
 * @brief Gets the current floor. 
 *
 * @return Return current floor. If no current floor return 0.
 */

int elevator_get_current_floor();

void elevator_set_current_floor();

void elevator_startup();

void travel_to_destination(int destination_floor);

void run_elevator();

