/**
 * @brief Gets the current direction. 
 *
 * @return Return current_direction.
 */
int get_current_direction();

/**
 * @brief Sets current_direction to @p direction .
 *
 * @param direction
 */
void set_current_direction(int direction);


/**
 * @brief Gets the value of elevator_order_array with index @p floor . 
 *
 * @param floor
 * 
 * @return Return the value of elevator_order_array with selected index.
 */
int get_order_at_floor(int floor);


/**
 * @brief Sets the value of elevator_order_array with index @p floor to @p order .
 *
 * @param floor
 * @param order
 */
void set_order_at_floor(int floor, int order);


/**
 * @brief Updates elevator_order_array if any of the order up buttons are pressed.
 */
void set_order_up();


/**
 * @brief Updates elevator_order_array if any of the order down buttons are pressed.
 */
void set_order_down();

/**
 * @brief Updates elevator_order_array if any of the order inside buttons are pressed.
 */
void set_order_inside();

/**
 * @brief Updates elevator_order_array if any order buttons are pressed.
 */
void handle_orders();


/**
 * @brief Checks if there are any order above @p starting_point .
 *
 * @param starting_point
 * 
 * @return Return 1 if there are orders above. Return 0 otherwise.
 */
int check_orders_above(int starting_point);

/**
 * @brief Checks if there are any order below @p starting_point .
 *
 * @param starting_point
 * 
 * @return Return 1 if there are orders below. Return 0 otherwise.
 */
int check_orders_below(int starting_point);

/**
 * @brief Gets the total amount of unattended orders.
 *
 * @return Return the total amount of unattended orders.
 */
int get_order_count();

/**
 * @brief Updates current_direction based on existing orders, current_direction
 * and last_direction.
 */
void update_current_direction();

/**
 * @brief Checks if there are any up orders at the current floor.
 *
 * @return Return 1 if up order at floor. Return 0 otherwise.
 */
int check_up_at_floor();

/**
 * @brief Checks if there are any down orders at the current floor.
 *
 * @return Return 1 if down order at floor. Return 0 otherwise.
 */
int check_down_at_floor();

/**
 * @brief Checks if there are any cab orders or up and down orders simultaneously at the current floor.
 *
 * @return Return 1 if cab order or up and down order at floor. Return 0 otherwise.
 */
int check_both_or_cab_at_floor();

/**
 * @brief Checks if the elevator has arrived at a floor with an order that needs to be attended.
 *
 * @return Return 1 if arrived at floor with order. Return 0 otherwise.
 */
int check_arrival();

/**
 * @brief Clears all existing orders in elevator_order_array.
 */
void clear_all_orders();

/**
 * @brief Prints all existing orders in elevator_order_array.
 */
void print_all_orders();

/**
 * @brief Checks if there are any orders at at @p floor .
 * 
 * @param floor
 * 
 * @return Return 1 if order at requested floor. Return 0 otherwise.
 */
int bool_order_at_floor(int floor);