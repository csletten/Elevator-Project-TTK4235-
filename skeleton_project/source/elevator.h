/**
 * @file
 * @brief Running elevator and updating states.  
 */


#include "hardware.h"

/**
 * @brief The possible states of the elevator.
 */
typedef enum {
    IDLE,
    RUNNING,
    EMERGENCY_STOP,
    FLOOR,
    OBSTRUCTED
} CurrentState;

/**
 * @brief The possible order types.
 */
typedef enum {
    UP = 1,
    DOWN,
    BOTH_OR_CAB
} OrderState;


/**
 * @brief Gets the current state. 
 *
 * @return Return state.
 */
int elevator_get_state();

/**
 * @brief Sets the state to @p new_state .  
 * 
 * @param new_state
 */
void elevator_set_state(CurrentState new_state);

/**
 * @brief Gets the current floor. 
 *
 * @return Return current_floor.
 */
int elevator_get_current_floor();

/**
 * @brief Gets FLOOR_COUNT.
 *   
 * @return Returns FLOOR_COUNT.
 */
int get_FLOOR_COUNT();

/**
 * @brief Gets BUTTON_COUNT.
 *    
 * @return Returns BUTTON_COUNT.
 */
int get_BUTTON_COUNT();


/**
 * @brief Checks the floor number. 
 *
 * @return Return current floor. Return 0 if between floors.
 */
int elevator_one_indexed_floor_number();

/**
 * @brief Updates the current_floor variable to the non-zero return value of elevator_one_indexed_floor_number()
 */
void elevator_update_current_floor();

/**
 * @brief Initialises the elevator and runs the elevator to the closest floor below.
 */
void elevator_startup();

/**
 * @brief Runs the elevator.
 */
void run_elevator();