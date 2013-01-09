/*
 * aufgabe4.c
 *
 *  Created on: 19.12.2012
 *      Author: roland
 */

#include "headers.h"

#define TAKT_TAKTGEBER_RATE				2				// defines takt rate of taktgeber in msec
#define WAIT_TAKTGEBER_WASTE_TIME		1		// waste time within wait_taktgeber in msec
#define N_TIMES_WAKE_UP_THREADS			10
#define WAIT_THREAD1_WASTE_TIME			4
#define WAIT_THREAD2_WASTE_TIME			4
#define NSEC_MAX 						(1000000000L-1)


static sem_t 	takt_sem,
				wait_thread1_sem,
				wait_thread2_sem;
static bool on_looping_flag = true;



void stop_looping_aufgabe4() {

	on_looping_flag = false;
}

void taktgeber(void *unused) {

	struct timespec request;
	int ret = 0;
	unsigned int takt = TAKT_TAKTGEBER_RATE * 1000000;

	dbg_h("Debug: Starting taktgeber thread.\n");

	/*initialisierung Semaphore */
	ret = sem_init(&takt_sem, 0, 0);
	if(ret == -1) {

		fprintf(stderr, "error: Semaphore init wait_thread1_sem.\n");
		print_error_code(errno);
	}

	set_priority(pthread_self(), TAKTGEBER_SCHEDULER, TAKTGEBER_SCHEDULER_PRIOR);

#ifdef DEBUG_HIGH
	print_priority(pthread_self(), NULL);
#endif

	do {
		ret = clock_gettime(KIND_OF_CLOCK, &request);
	}while(errno == EINTR);
	if(ret) {

		fprintf(stderr, "error: Taktgeber - clock_gettime.\n");
		print_error_code(ret);
	}

	while(on_looping_flag) {



		/*
		 * IMPORTANT: Checking and handling nsec field overrrun.
		 * This will cause clock_nanosleep to return EINVAL
		 */
		if((NSEC_MAX - takt) > request.tv_nsec) {

			request.tv_nsec += takt;

		}
		else {

			request.tv_sec++;
			request.tv_nsec -= NSEC_MAX - takt;
		}

		dbg_h("Debug: Taktgeber sleeping until sec: %ld - msec: %f.\n", request.tv_sec, (double)request.tv_nsec/1000000);

		/*
		 * CLOCK_REALTIME, weil schlafen f�r eine absolute Zeitdauer
		 */
		do {
			ret = clock_nanosleep(KIND_OF_CLOCK, TIMER_ABSTIME, &request, NULL);
		}while(errno == EINTR);
		if(ret) {

			fprintf(stderr, "error: Taktgeber - clock_nanosleep.\n");
			print_error_code(ret);
		}

		ret = sem_post(&takt_sem);
		if(ret == -1) {

			fprintf(stderr, "error: Semaphore post takt_sem.\n");
			print_error_code(errno);
		}

	}

	/* Thread beenden - Ohne Rückgabewert */
	ret = sem_destroy(&takt_sem);
	if(ret == -1) {

		fprintf(stderr, "error: Semaphore destroy takt_sem.\n");
		print_error_code(errno);
	}

	pthread_exit(NULL);

}


void wait_taktgeber(void *unused) {

	int ret = 0, i = 0;

	set_priority(pthread_self(), WAIT_TAKTGEBER_SCHEDULER, WAIT_TAKTGEBER_SCHEDULER_PRIOR);

	/*initialisierung Semaphore */
	sem_init(&wait_thread1_sem, 0, 0);
	if(ret == -1) {

		fprintf(stderr, "error: Semaphore init wait_thread1_sem.\n");
		print_error_code(errno);
	}
	sem_init(&wait_thread2_sem, 0, 0);
	if(ret == -1) {

		fprintf(stderr, "error: Semaphore init wait_thread1_sem.\n");
		print_error_code(errno);
	}

#ifdef DEBUG_HIGH
	print_priority(pthread_self(), NULL);
#endif

	while(on_looping_flag) {

		ret = sem_wait(&takt_sem);
		if(ret == -1) {

			fprintf(stderr, "error: Semaphore wait takt_sem.\n");
			print_error_code(errno);
		}
		dbg_h("Debug: Takt semaphore arrived.\n");
		waste_time(WAIT_TAKTGEBER_WASTE_TIME);
		i++;

		if(i % N_TIMES_WAKE_UP_THREADS == 0) {
			ret = sem_post(&wait_thread1_sem);
			if(ret == -1) {

				fprintf(stderr, "error: Semaphore post wait_thread1_sem.\n");
				print_error_code(errno);
			}

			ret = sem_post(&wait_thread2_sem);
			if(ret == -1) {

				fprintf(stderr, "error: Semaphore post wait_thread2_sem.\n");
				print_error_code(errno);
			}
		}

	}

	/* Thread beenden - Ohne Rückgabewert */
	ret = sem_destroy(&wait_thread1_sem);
	if(ret == -1) {

		fprintf(stderr, "error: Semaphore destroy wait_thread1_sem.\n");
		print_error_code(errno);
	}

	ret = sem_destroy(&wait_thread2_sem);
	if(ret == -1) {

		fprintf(stderr, "error: Semaphore destroy wait_thread2_sem.\n");
		print_error_code(errno);
	}

	pthread_exit(NULL);
}


void wait_thread1(void *unused) {

	int ret = 0;

	set_priority(pthread_self(), WAIT_THREAD1_SCHEDULER, WAIT_THREAD1_SCHEDULER_PRIOR);

#ifdef DEBUG_HIGH
	print_priority(pthread_self(), NULL);
#endif

	while(on_looping_flag) {

		ret = sem_wait(&wait_thread1_sem);
		if(ret == -1) {

			fprintf(stderr, "error: Semaphore wait wait_thread1_sem.\n");
			print_error_code(errno);
		}
		dbg_h("Debug: wait_thread1 active.\n");
		waste_time(WAIT_THREAD1_WASTE_TIME);
	}

	/* Thread beenden - Ohne Rueckgabewert */
	pthread_exit(NULL);
}


void wait_thread2(void *unused) {

	int ret = 0;

	set_priority(pthread_self(), WAIT_THREAD2_SCHEDULER, WAIT_THREAD2_SCHEDULER_PRIOR);

#ifdef DEBUG_HIGH
	print_priority(pthread_self(), NULL);
#endif

	while(on_looping_flag) {

		ret = sem_wait(&wait_thread2_sem);
		if(ret == -1) {

			fprintf(stderr, "error: Semaphore wait wait_thread2_sem.\n");
			print_error_code(errno);
		}
		dbg_h("Debug: wait_thread2 active.\n");
		waste_time(WAIT_THREAD2_WASTE_TIME);
	}

	/* Thread beenden - Ohne Rueckgabewert */
	pthread_exit(NULL);
}

