/**
 * @file
 * @brief All functions handling the lights.
 */

/**
 * @brief Enables the lights for the order up buttons if order up buttons are pressed.
 */
void lights_set_order_lights_up();

/**
 * @brief Disables the lights for the order up buttons depending on the existing orders
 * in elevator_queue_array.
 */
void lights_clear_order_lights_up();

/**
 * @brief Enables the lights for the order down buttons if order down buttons are pressed.
 */
void lights_set_order_lights_down();

/**
 * @brief Disables the lights for the order down buttons depending on the existing orders
 * in elevator_queue_array.
 */
void lights_clear_order_lights_down();

/**
 * @brief Enables the lights for the cab order buttons if cab order buttons are pressed.
 */
void lights_set_order_lights_inside();

/**
 * @brief Disables the lights for the cab order buttons depending on the existing orders
 * in elevator_queue_array.
 */
void lights_clear_order_lights_inside();

/**
 * @brief Sets the stop light if the stop button is pressed. Disables otherwise.
 */
void lights_set_stop_light();

/**
 * @brief Sets the floor light to the last floor the elevator passed.
 */
void lights_set_floor_lights();

/**
 * @brief Enables and disables all the elevator lights.
 */
void lights_set_and_clear_lights();