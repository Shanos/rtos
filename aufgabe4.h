/*
 * aufgabe4.h
 *
 *  Created on: 19.12.2012
 *      Author: roland
 */

#ifndef AUFGABE4_H_
#define AUFGABE4_H_

#include "headers.h"

__BEGIN_DECLS

/**
 * @brief Stop infinity loop within threads
 *
 * Function will be called through signal handler
 */
void stop_looping_aufgabe4(void);

/**
 * @brief Create clock rate TAKT_TAKTGEBER_RATE
 * @param unused Not used yet
 * @return void No return value
 *
 * Thread is created in main.
 * Thread create clock rate TAKT_TAKTGEBER_RATE and post frequently a semaphore
 */
void taktgeber(void *unused);

/**
 * @brief Post semaphore for wait_thread1 and wait_thread2
 * @param unused Not used yet
 * @return void No return value
 *
 * Thread is created in main.
 * Thread wake up wait_thread1 and wait_thread2 and waste time WAIT_TAKTGEBER_WASTE_TIME
 */
void wait_taktgeber(void *unused);

/**
 * @brief Wait for semaphore and just waste time WAIT_THREAD1_WASTE_TIME
 * @param unused Not used yet
 * @return void No return value
 *
 * Thread is created in main.
 * Thread Wait for semaphore and just waste time WAIT_THREAD1_WASTE_TIME
 */
void wait_thread1(void *unused);

/**
 * @brief Wait for semaphore and just waste time WAIT_THREAD2_WASTE_TIME
 * @param unused Not used yet
 * @return void No return value
 *
 * Thread is created in main.
 * Thread Wait for semaphore and just waste time WAIT_THREAD2_WASTE_TIME
 */
void wait_thread2(void *unused);



__END_DECLS

#endif /* AUFGABE4_H_ */
