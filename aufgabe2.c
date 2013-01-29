/*
 * aufgabe2.c
 *
 *  Created on: 07.12.2012
 *      Author: roland
 */

#include "headers.h"

#define WAIT_MINIMUM 50000 	/* minimum of usec for rein raus */
#define BOUNCE 200			/* limit for random number */

static bool on_looping_flag = true;

unsigned int get_random(unsigned int bounce) {

	static unsigned int random = 0;

	if(!random) {

		random = time(NULL);
		if(random == -1) {

			fprintf(stderr, "error: Random number failure, calendar time is not available.\n");
			return WAIT_MINIMUM;
		}
	}

	random = random * 1103515245 + 12345;
	random = random % bounce + 1;
	dbg("Debug: Random number %d.\n", random);

	return random * WAIT_MINIMUM;

}

void stop_looping_aufgabe2() {

	on_looping_flag = false;
}


void ausgabe_raumbelegung(void *raum) {

	int ret = 0;
	raum_t *raum_tmp = (raum_t *)raum;

	set_priority(pthread_self(), AUSGABE_RAUMBELEGUNG_SCHEDULER, AUSGABE_RAUMBELEGUNG_SCHEDULER_PRIOR);

#ifdef DEBUG_HIGH
	print_priority(pthread_self(), NULL);
#endif

	while(on_looping_flag) {

		ret = pthread_mutex_lock(&raum_tmp->raum_lock);
		if(ret) {

			fprintf(stderr, "error: Ausgabe Raumbelegung - pthread_mutex_lock.\n");
			print_error_code(ret);
		}

		ret = pthread_cond_wait(&raum_tmp->raumaenderung, &raum_tmp->raum_lock);
		if(ret) {

			fprintf(stderr, "error: Ausgabe Raumbelegung - pthread_cond_wait.\n");
			print_error_code(ret);
		}

		printf("Anzahl Personen im Raum: %d\n", raum_tmp->raumbelegung);
		ret = pthread_mutex_unlock(&raum_tmp->raum_lock);
		if(ret) {

			fprintf(stderr, "error: Ausgabe Raumbelegung - pthread_mutex_unlock.\n");
			print_error_code(ret);
		}
	}

	/* Thread beenden - Ohne Rückgabewert */
	pthread_exit(NULL);
}

void rein_raus(void *raum) {

	int ret = 0;
	raum_t *raum_tmp = (raum_t *)raum;

	set_priority(pthread_self(), REIN_RAUS_SCHEDULER, REIN_RAUS_SCHEDULER_PRIOR);

#ifdef DEBUG_HIGH
	print_priority(pthread_self(), NULL);
#endif

	while(on_looping_flag) {

		ret = pthread_mutex_lock(&raum_tmp->raum_lock);
		if(ret) {

			fprintf(stderr, "error: Rein raus - pthread_mutex_lock.\n");
			print_error_code(ret);
		}

		raum_tmp->raumbelegung++;
		ret = pthread_cond_broadcast(&raum_tmp->raumaenderung);
		if(ret) {

			fprintf(stderr, "error: Rein raus - pthread_cond_broadcast.\n");
			print_error_code(ret);
		}

		ret = pthread_mutex_unlock(&raum_tmp->raum_lock);
		if(ret) {

			fprintf(stderr, "error: Rein raus - pthread_mutex_unlock.\n");
			print_error_code(ret);
		}

		ret = usleep(get_random(BOUNCE));
		if(ret) {

			fprintf(stderr, "error: Rein raus - usleep.\n");
			print_error_code(errno);
		}

		ret = pthread_mutex_lock(&raum_tmp->raum_lock);
		if(ret) {

			fprintf(stderr, "error: Rein raus - pthread_mutex_lock.\n");
			print_error_code(ret);
		}

		raum_tmp->raumbelegung--;
		ret = pthread_cond_broadcast(&raum_tmp->raumaenderung);
		if(ret) {

			fprintf(stderr, "error: Rein raus - pthread_cond_broadcast.\n");
			print_error_code(ret);
		}

		ret = pthread_mutex_unlock(&raum_tmp->raum_lock);
		if(ret) {

			fprintf(stderr, "error: Rein raus - pthread_mutex_unlock.\n");
			print_error_code(ret);
		}

		ret = usleep(get_random(BOUNCE));
		if(ret) {

			fprintf(stderr, "error: Rein raus - usleep.\n");
			print_error_code(errno);
		}
	}

	/* Thread beenden - Ohne Rückgabewert */
	pthread_exit(NULL);
}
