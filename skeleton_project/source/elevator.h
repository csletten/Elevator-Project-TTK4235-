#include "hardware.h"

typedef enum {
    IDLE,
    RUNNING,
    EMERGENCY_STOP,
    DOOR,
    OBSTRUCT
} CurrentState;

typedef enum {
    UP = 1,
    DOWN,
    BOTH_OR_INSIDE
} OrderState;

/**
 * @brief Gets the current floor. 
 *
 * @return Return current floor. If no current floor return 0.
 */
int elevator_get_current_floor();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void elevator_set_current_floor();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void order_buttons_up();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void clear_order_buttons_up();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void order_buttons_down();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void clear_order_buttons_down();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void order_buttons_inside();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void clear_order_buttons_inside();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void stop_button();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void floor_lights();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void handle_buttons();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void clear_all_orders();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
int get_destination();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void set_direction(int destination);

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
void elevator_startup();

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param destination_floor Destination floor.
 */
void travel_to_destination(int destination_floor);

/**
 * @brief Runs the elevator.
 */
void run_elevator();

