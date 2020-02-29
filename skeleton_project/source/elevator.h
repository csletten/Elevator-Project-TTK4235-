#include "hardware.h"

typedef enum {
    IDLE,
    RUNNING,
    EMERGENCY_STOP,
    FLOOR,
    OBSTRUCTED
} CurrentState;

typedef enum {
    UP = 1,
    DOWN,
    BOTH_OR_CAB
} OrderState;

int get_state();

void set_state(CurrentState new_state);

int get_current_floor();

int get_FLOOR_COUNT();

int get_BUTTON_COUNT();


/**
 * @brief Gets the current floor. 
 *
 * @return Return current floor. If no current floor return 0.
 */
int check_floor_number();

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
void update_current_floor();

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
 * @brief Runs the elevator.
 */
void run_elevator();

