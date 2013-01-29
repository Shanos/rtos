/*
 * priority.h
 *
 *  Created on: 15.12.2012
 *      Author: roland
 */

#ifndef PRIORITY_H_
#define PRIORITY_H_

#include "headers.h"

__BEGIN_DECLS

#define KIND_OF_CLOCK							CLOCK_REALTIME
//#define KIND_OF_CLOCK							CLOCK_MONOTONIC

#define INIT_WASTE_TIME_SCHEDULER 				SCHED_FIFO
#define INIT_WASTE_TIME_SCHEDULER_PRIOR 		255

#define REIN_RAUS_SCHEDULER						SCHED_FIFO
#define REIN_RAUS_SCHEDULER_PRIOR				20

#define AUSGABE_RAUMBELEGUNG_SCHEDULER			SCHED_FIFO
#define AUSGABE_RAUMBELEGUNG_SCHEDULER_PRIOR	30

#define TAKTGEBER_SCHEDULER						SCHED_FIFO
#define TAKTGEBER_SCHEDULER_PRIOR				40

#define WAIT_TAKTGEBER_SCHEDULER				SCHED_FIFO
#define WAIT_TAKTGEBER_SCHEDULER_PRIOR			35

#define WAIT_THREAD1_SCHEDULER					SCHED_FIFO
#define WAIT_THREAD1_SCHEDULER_PRIOR			33

#define WAIT_THREAD2_SCHEDULER					SCHED_FIFO
#define WAIT_THREAD2_SCHEDULER_PRIOR			33

struct _scheduler {

	int policy;
	int priority;
	int max_priority;
	int min_priority;
};

/**
 * @brief Request priority of the thread
 * @param id ID of the thread
 * @param scheduler Storage location
 * @retval false no Storage location is given
 * @retval true On success
 *
 * Function request the priorities (Policy, Priority, PriorityMin, PriorityMax)
 * of the given thread.
 * It will be saved into scheduler structure
 */
bool get_priority(pthread_t id, struct _scheduler *scheduler);

/**
 * @brief Print priority of the thread
 * @param id ID of the thread
 * @param scheduler Print scheduler structure
 * @retval false Could not call get_priority
 * @retval true On success
 *
 * Function prints the priorities (Policy, Priority, PriorityMin, PriorityMax)
 * If no scheduler structure is given, function call get_priority and store it
 * in the scheduler
 */
bool print_priority(pthread_t id, struct _scheduler *scheduler);

/**
 * @brief Set priority of the thread
 * @param id ID of the thread
 * @param policy New policy of the thread
 * @param priority New priority of the thread
 * @retval false Priority could not set
 * @retval true On success
 *
 * Function set the policy and priority
 * of the given thread.
 */
bool set_priority(pthread_t id, int policy, int priority);



__END_DECLS

#endif /* PRIORITY_H_ */
