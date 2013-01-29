
#include "headers.h"

static void signals_handler() {

	printf("Program will be stopped.\n");

	stop_looping_aufgabe2();
	stop_looping_aufgabe3();
	stop_looping_aufgabe4();

}

int main(int argc, char *argv[]) {

	pthread_t ausgabe_id, takt_id, wait_takt_id, wait_thread1_id, wait_thread2_id;
	raum_t raum;
	int i=0, ret = 0;
	raum.raumbelegung=0;

	/* Setup signals */
	signal(SIGINT, signals_handler);
	signal(SIGHUP, signals_handler);
	signal(SIGTERM, signals_handler);
	
	init_waste_time();

	/*initialisierung Mutex & Condition*/
	ret = pthread_mutex_init(&raum.raum_lock, NULL);
	if(ret) {

		fprintf(stderr, "error: Main - pthread_mutex_init.\n");
		print_error_code(ret);
	}

	ret = pthread_cond_init(&raum.raumaenderung, NULL);
	if(ret) {

		fprintf(stderr, "error: Main - pthread_cond_init.\n");
		print_error_code(ret);
	}



	/* Anlegen der Threads */
	ret = pthread_create(&ausgabe_id, NULL,(void *)&ausgabe_raumbelegung, (void *)&raum);
	if(ret) {

		fprintf(stderr, "error: Ausgabe Raumbelegung - pthread_create.\n");
		print_error_code(ret);
		return EXIT_FAILURE;
	}
	else
		dbg("Debug: Thread Ausgabe Raumbelegung [%d] started.\n", ausgabe_id);

	for(i=0; i<PERSONEN; i++) {

		ret = pthread_create(&raum.threads[i], NULL,(void *)&rein_raus, (void *)&raum);
		if(ret) {

			fprintf(stderr, "error: Rein raus [%d] - pthread_create.\n", i);
			print_error_code(ret);
			return EXIT_FAILURE;
		}
		else
			dbg("Debug: Thread rein raus [%d] started.\n", raum.threads[i]);
	}


	ret = pthread_create(&takt_id, NULL,(void *)&taktgeber, NULL);
	if(ret) {

		fprintf(stderr, "error: Taktgeber - pthread_create.\n");
		print_error_code(ret);
		return EXIT_FAILURE;
	}
	else
		dbg("Debug: Thread Taktgeber [%d] started.\n", takt_id);

	ret = pthread_create(&wait_takt_id, NULL,(void *)&wait_taktgeber, NULL);
	if(ret) {

		fprintf(stderr, "error: Wait taktgeber - pthread_create.\n");
		print_error_code(ret);
		return EXIT_FAILURE;
	}
	else
		dbg("Debug: Thread Wait Taktgeber [%d] started.\n", wait_takt_id);

	ret = pthread_create(&wait_thread1_id, NULL,(void *)&wait_thread1, NULL);
	if(ret) {

		fprintf(stderr, "error: Wait thread1 - pthread_create.\n");
		print_error_code(ret);
		return EXIT_FAILURE;
	}
	else
		dbg("Debug: Thread Wait thread1 [%d] started.\n", wait_thread1_id);

	ret = pthread_create(&wait_thread2_id, NULL,(void *)&wait_thread2, NULL);
	if(ret) {

		fprintf(stderr, "error: Wait thread2 - pthread_create.\n");
		print_error_code(ret);
		return EXIT_FAILURE;
	}
	else
		dbg("Debug: Thread Wait thread2 [%d] started.\n", wait_thread2_id);





	/* Auf das Ende der Threads warten */
	for(i=0; i<PERSONEN; i++) {

		ret = pthread_join(raum.threads[i], NULL);
		if(ret) {

			fprintf(stderr, "error: Thread Rein raus [%d] - pthread_join.\n", i);
			print_error_code(ret);
		}
		else
			dbg("Debug: Thread rein raus [%d] finished.\n", raum.threads[i]);

	}

	ret = pthread_join(ausgabe_id, NULL);
	if(ret) {

		fprintf(stderr, "error: Thread Ausgabe Raumbelegung - pthread_join.\n");
		print_error_code(ret);
	}
	else
		dbg("Debug: Thread Ausgabe Raumbelegung [%d] finished.\n", ausgabe_id);


	ret = pthread_join(wait_thread1_id, NULL);
	if(ret) {

		fprintf(stderr, "error: Thread wait thread1 - pthread_join.\n");
		print_error_code(ret);
	}
	else
		dbg("Debug: Thread wait thread1 [%d] finished.\n", wait_thread1_id);

	ret = pthread_join(wait_thread2_id, NULL);
	if(ret) {

		fprintf(stderr, "error: Thread wait thread2 - pthread_join.\n");
		print_error_code(ret);
	}
	else
		dbg("Debug: Thread wait thread2 [%d] finished.\n", wait_thread2_id);

	ret = pthread_join(wait_takt_id, NULL);
	if(ret) {

		fprintf(stderr, "error: Thread wait taktgeber - pthread_join.\n");
		print_error_code(ret);
	}
	else
		dbg("Debug: Thread wait taktgeber [%d] finished.\n", wait_takt_id);

	ret = pthread_join(takt_id, NULL);
	if(ret) {

		fprintf(stderr, "error: Thread taktgeber - pthread_join.\n");
		print_error_code(ret);
	}
	else
		dbg("Debug: Thread taktgeber [%d] finished.\n", takt_id);



	return EXIT_SUCCESS;
}



