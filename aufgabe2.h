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

unsigned int get_random(unsigned int bounce);
void stop_looping_aufgabe2(void);
void ausgabe_raumbelegung(void *raum);
void rein_raus(void *raum);


__END_DECLS

#endif /* AUFGABE2_H_ */
