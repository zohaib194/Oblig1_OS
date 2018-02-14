#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SHARED 0

sem_t sem[6];

struct threadargs {
int id; /* thread number */
int sec; /* how many seconds to sleep */
int signal[6]; /* which threads to signal when done */
};


void *tfunc(void *arg) {
	struct threadargs *targs=arg;
	
	// Waiting to enter critical region. 
	sem_wait(&sem[targs->id]);
	
	// Print all the stuff to screen about a thread.
	printf("Prosess %d kjører\n", targs->id);

	printf("Prosess %d skal kjøre i %d sekunder\n", targs->id, targs->sec);

	sleep(targs->sec);	// Sleep.

	printf("Process %d er ferdig\n", targs->id); 	
								// Done with critical region,
	sem_post(&sem[targs->id]); 	// awake the threads waiting in sem_wait();
	for(int i = 0; i < 6; i++){
		if (targs->signal[i] == 1){	// Invoke the thread which needs to be invoked in signal
			sem_post(&sem[i]);

		}
	}
	pthread_exit(0);
}

int main(void){
	int i, j;
	struct threadargs *targs[6];
	pthread_t threads[6];

	/* allocate memory for threadargs and zero out semaphore signals */
	for (i=0;i<6;i++) {
		targs[i] = (struct threadargs*) malloc(sizeof(struct threadargs));
		targs[i]->id = 0;
		targs[i]->sec = 0;
		for (j=0;j<6;j++) {
			targs[i]->signal[j]=0;
		}
	}

	/* Set data for all the threads */
	for(i=0; i <6; i++){
		targs[i]->id = i;
		if(i == 0){
			targs[i]->sec = 1;
			targs[i]->signal[1] = 1;
			targs[i]->signal[4] = 1;
		}
		if (i == 1 || i == 3) {
			targs[i]->sec = 2;
			if(i == 1) {
			 targs[i]->signal[3] = 1; 
			}
		}
		if (i == 2 || i == 4 || i == 5){
			targs[i]->sec = 3;
			if (i == 4) {
				targs[i]->signal[5] = 1;
			}
		}
	}

	/* Print all data of each thread */
	for (int prt = 0 ; prt < 6; prt++){
		printf("Id: %d, Seconds to sleep: %d, Signal: ,",targs[prt]->id, targs[prt]->sec);
		for(int prt2 = 0; prt2 < 6; prt2++){
			printf("%d,",targs[prt]->signal[prt2]);
		}
	}

	/* Initializing and starting threads */
	for(int x = 0; x < 6; x++){	
		if(x == 0 || x == 2){
			sem_init(&sem[x], SHARED, 1);
		} else { 
			// Sem, if its shared between process, is it going to wait for other threads
			sem_init(&sem[x], SHARED, 0);
		}
		pthread_create(&threads[x], NULL, tfunc, (void*) targs[x]);
	}

	/* Wait for all threads */
	for(int z = 5; z >= 0; z--){
		pthread_join(threads[z], NULL);		
	} 
	
	/* Free the memory */
	free(targs);
	
	return 0;
}