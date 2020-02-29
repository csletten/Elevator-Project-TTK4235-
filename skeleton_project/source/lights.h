/**
 * @brief Enables the lights for the order up buttons if order up buttons are pressed.
 */
void set_order_lights_up();

/**
 * @brief Disables the lights for the order up buttons depending on the existing orders
 * in elevator_queue_array.
 */
void clear_order_lights_up();

/**
 * @brief Enables the lights for the order down buttons if order down buttons are pressed.
 */
void set_order_lights_down();

/**
 * @brief Disables the lights for the order down buttons depending on the existing orders
 * in elevator_queue_array.
 */
void clear_order_lights_down();

/**
 * @brief Enables the lights for the cab order buttons if cab order buttons are pressed.
 */
void set_order_lights_inside();

/**
 * @brief Disables the lights for the cab order buttons depending on the existing orders
 * in elevator_queue_array.
 */
void clear_order_lights_inside();

/**
 * @brief Sets the stop light if the stop button is pressed. Disables otherwise.
 */
void set_stop_light();

/**
 * @brief Sets the floor light to the last floor the elevator passed.
 */
void set_floor_lights();

/**
 * @brief Enables and disables all the elevator lights.
 */
void handle_lights();