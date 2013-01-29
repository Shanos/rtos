/*
 * aufgabe3.h
 *
 *  Created on: 07.12.2012
 *      Author: roland
 */

#ifndef AUFGABE3_H_
#define AUFGABE3_H_

__BEGIN_DECLS


/**
 * @brief Stop waste time
 *
 * Function will be called through signal handler
 */
void stop_looping_aufgabe3(void);

/**
 * @brief Set calculated loop counter thread safe
 * @param a_count_loops calculated loop counter to store
 * @retval false Failure mutex lock or unlock
 * @retval true On success
 *
 * Function set calculated loop counter thread safe.
 */
bool set_count_loops(unsigned int a_count_loops);

/**
 * @brief Get calculated loop counter thread safe
 * @param a_count_loops calculated loop counter to store
 * @retval 0 Failure mutex lock or unlock
 * @retval >0 On success counted loops
 *
 * Function get the stored loop counter thread safe.
 */
unsigned int get_count_loops(void);

/**
 * @brief Waste amount of milliseconds
 * @param msec Wasted millisecond
 * @retval false Exceed time limit
 * @retval true On success
 *
 * Function waste time without hardware support.
 * Run a certain value in a loop.
 * Function can be stopped by signal handler.
 */
bool waste_time(unsigned int msec);

/**
 * @brief Determine loop counter for waste time
 * @retval false Ticks could not be determined by clock()
 * @retval true On success
 *
 * Function determine the loop counter for 1 msec,
 * use waste_time for calculation.
 */
bool init_waste_time(void);


__END_DECLS

#endif /* AUFGABE3_H_ */
