/*
 * aufgabe2.h
 *
 *  Created on: 07.12.2012
 *      Author: roland
 */

#ifndef AUFGABE2_H_
#define AUFGABE2_H_

__BEGIN_DECLS

#define PERSONEN 10


typedef struct _Raum
{
	pthread_mutex_t raum_lock;
	pthread_cond_t raumaenderung;
	pthread_t threads[PERSONEN];
	int raumbelegung;

}raum_t;

/**
 * @brief Stop infinity loop within threads
 *
 * Function will be called through signal handler
 */
void stop_looping_aufgabe2(void);

/**
 * @brief Get random number for rein_raus
 * @param bounce Upper bounce fpr random number
 * @retval WAIT_MINIMUM On failure
 * @retval Random On success
 *
 * Function calculate the next random number for rein_raus with a upper bounce.
 * On failure a fix value of WAIT_MINIMUM will be returned.
 */
unsigned int get_random(unsigned int bounce);

/**
 * @brief Get random number for rein_raus
 * @param raum Structure raum
 *
 * Function prints the raumbelegung. Can be stopped by signal handler
 */
void ausgabe_raumbelegung(void *raum);

/**
 * @brief Simulate people
 * @param raum Structure raum
 *
 * Function simulate people which going in and out of a room.
 * Can be stopped by signal handler
 */
void rein_raus(void *raum);


__END_DECLS

#endif /* AUFGABE2_H_ */
