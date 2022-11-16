/**
 * @file
 * @brief Time functions.
 * 
 * Functions used to keep doors open for 3 seconds etc. 
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Starts a timer that expires after @p msec seconds. 
 *
 * @param msec
 */
void timer_start_timer(int msec);

/**
 * @brief Checks if the timer has expired.
 *
 * @return Return 1 if the timer has expired. Return 0 otherwise.
 */
int timer_check_expired();

/**
 * @brief Prints the elapsed time since the timer was started.
 */
void timer_print_current_time();

/**
 * @brief Starts a 5 second timer and prints the elapsed time.
 */
void timer_test_timer();