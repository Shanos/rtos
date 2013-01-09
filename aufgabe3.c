/*
 * aufgabe3.c
 *
 *  Created on: 07.12.2012
 *      Author: roland
 */

#include "headers.h"

#define PRECISION_WASTE_TIME 			1000 		// 1 us
#define INIT_WASTE_TIME_LOWER_BOUND		0
#define INIT_WASTE_TIME_UPPER_BOUND		500000


static bool on_looping_flag = true;
static volatile unsigned int count_loops = 0;
static pthread_mutex_t count_loops_lock = PTHREAD_MUTEX_INITIALIZER;

void stop_looping_aufgabe3() {

	on_looping_flag = false;
}

bool set_count_loops(unsigned int a_count_loops){

	pthread_mutex_lock(&count_loops_lock);
	count_loops = a_count_loops;
	pthread_mutex_unlock(&count_loops_lock);
	dbg_h("Debug: Set loop counter %u.\n", count_loops);

	return true;
}

unsigned int get_count_loops(){

	unsigned int ret = 0;
	pthread_mutex_lock(&count_loops_lock);
	ret = count_loops;
	pthread_mutex_unlock(&count_loops_lock);
	dbg_h("Debug: Get loop counter %u.\n", ret);

	return ret;
}


bool waste_time(unsigned int msec) {

	unsigned int i, j, counter = get_count_loops();

	for(i=0; i<msec; i++) {

		for(j=0; j<counter; j++) {

			if(!on_looping_flag)
				break;
		}

		if(!on_looping_flag)
			break;
	}
	return true;
}


bool init_waste_time() {

	struct _scheduler scheduler;
	struct timespec start, end, res;
	int diff = 0, ret = 0;
	unsigned int unten = INIT_WASTE_TIME_LOWER_BOUND, oben = INIT_WASTE_TIME_UPPER_BOUND;

	dbg("Debug: Trying to init waste time.\n");
	get_priority(pthread_self(), &scheduler);
	set_priority(pthread_self(), INIT_WASTE_TIME_SCHEDULER, INIT_WASTE_TIME_SCHEDULER_PRIOR);


#ifdef DEBUG_HIGH
	print_priority(pthread_self(), NULL);
#endif

	do {

		set_count_loops((oben+unten)/2);
		do {
			ret = clock_gettime(KIND_OF_CLOCK, &start);
		}while(errno == EINTR);
		if(ret) {

			fprintf(stderr, "error: Init waste time - clock_gettime.\n");
			print_error_code(ret);
			return false;
		}

		waste_time(1);

		do {
			ret = clock_gettime(KIND_OF_CLOCK, &end);
		}while(errno == EINTR);
		if(ret) {

			fprintf(stderr, "error: Init waste time - clock_gettime.\n");
			print_error_code(ret);
			return false;
		}

		diff = end.tv_nsec - start.tv_nsec;
		diff -= 1000000;							/* minus 1 ms */

		if(diff < 0) {

			unten = count_loops;
		}
		else {

			oben = count_loops;
		}

		printf("Debug: Loop counter: %u \t oben: %u \t unten: %u.\n", count_loops, oben, unten);

	}while(on_looping_flag&& !(abs(diff) <= PRECISION_WASTE_TIME));

	set_priority(pthread_self(), scheduler.policy, scheduler.priority);

#ifdef DEBUG_HIGH
	print_priority(pthread_self(), NULL);
#endif

	do {
		ret = clock_getres(KIND_OF_CLOCK, &res);
	}while(errno == EINTR);
	if(ret) {

		fprintf(stderr, "error: Init waste time - clock_getres.\n");
		print_error_code(ret);
		return false;
	}

	dbg("\tResolution clock [ns]: %ld.\n", res.tv_nsec);
	dbg("\tDeltaT [s] : %u.\n", end.tv_sec - start.tv_sec);
	dbg("\tDeltaT [ms]: %f.\n", ((double)(end.tv_nsec - start.tv_nsec)) / 1000000);
	dbg("\tDeltaT [us]: %f.\n", ((double)(end.tv_nsec - start.tv_nsec)) / 1000);
	dbg("\tDeltaT [ns]: %ld.\n", (end.tv_nsec - start.tv_nsec));
	printf("\tLoop counter: %u.\n", get_count_loops());

	return true;
}

void check_waste_time() {

	struct _scheduler scheduler;
	clock_t start, end;
	unsigned int maximum_waste_time = 10;


	get_priority(pthread_self(), &scheduler);
	set_priority(pthread_self(), INIT_WASTE_TIME_SCHEDULER, INIT_WASTE_TIME_SCHEDULER_PRIOR);
	set_count_loops(100000000);
	do {
		start = clock();
	}while(errno == EINTR);
	if(start == -1) {

		fprintf(stderr, "error: Check waste time - clock (start).\n");
		print_error_code(start);
	}


	waste_time(maximum_waste_time);

	do {
		end = clock();
	}while(errno == EINTR);
	if(end == -1) {

		fprintf(stderr, "error: Check waste time - clock (end).\n");
		print_error_code(end);
	}

	set_count_loops((unsigned int)(((maximum_waste_time*(double)get_count_loops())/(end - start))*1000));
	set_priority(pthread_self(), scheduler.policy, scheduler.priority);

	printf("\tDeltaT [Ticks] : %u.\n", end - start);
	printf("\tDeltaT [s]: %f.\n", ((float)(end - start)) / CLOCKS_PER_SEC);
	printf("\tCalculated Loop counter: %u.\n", get_count_loops());

}
