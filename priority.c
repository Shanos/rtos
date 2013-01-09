/*
 * priority.c
 *
 *  Created on: 15.12.2012
 *      Author: roland
 */
#include "headers.h"

bool get_priority(pthread_t id, struct _scheduler *scheduler) {

	int policy, result = 0;
	struct sched_param param;

	if(!scheduler) {

		fprintf(stderr, "error: No scheduler defined.\n");
		return false;
	}

	dbg_h("Debug: Trying to get priority.\n");
	result = pthread_getschedparam(id, &policy, &param);
	if(result == 0) {

		scheduler->policy = policy;
		scheduler->priority = param.sched_curpriority;

	}
	else {

		fprintf(stderr, "error: Priority could not print for thread %d.\n", id);
		print_error_code(result);
	}

	result = sched_get_priority_max(policy);
	if(result < 0) {

		fprintf(stderr, "error: Getting max priority.\n");
		print_error_code(errno);
	}
	else {

		scheduler->max_priority = result;
	}


	result = sched_get_priority_min(policy);
	if(result < 0) {

		fprintf(stderr, "error: Getting min priority.\n");
		print_error_code(errno);
	}
	else {

		scheduler->min_priority = result;
	}

	return true;

}

bool print_priority(pthread_t id, struct _scheduler *scheduler) {

	struct _scheduler scheduler_tmp;

	if(!scheduler) {

		scheduler = &scheduler_tmp;

		if(!get_priority(id, scheduler)) {

			fprintf(stderr, "error: Getting priority values.\n");
			return false;
		}
	}

	dbg_h("Debug: Trying to print priority.\n");

	printf("Thread %d:\n", id);
	printf("Policy: ");
	switch(scheduler->policy) {
		case SCHED_OTHER:
			printf("SCHED_OTHER; ");
			break;

		case SCHED_FIFO:
			printf("SCHED_FIFO; ");
			break;

		case SCHED_RR:
			printf("SCHED_RR; ");
			break;

		default:
			printf("unknown; ");
			break;
	}

	printf("\nPriority: %d\n", scheduler->priority);
	printf("Maximum priority %d:\n", scheduler->max_priority);
	printf("Minimum priority %d:\n", scheduler->min_priority);

	return true;
}

bool set_priority(pthread_t id, int policy, int priority) {

	int result = 0;
	struct sched_param param;
	param.sched_priority = priority;

	dbg_h("Debug: Trying to set priority.\n");
	result = pthread_setschedparam(id, policy, &param);
	if(result) {

		fprintf(stderr, "error: Priority could not set for thread: %d.\n", id);
		print_error_code(result);
	}

	return true;
}
