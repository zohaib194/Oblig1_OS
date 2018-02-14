#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMBER_OF_PHILOSOPHERS 5
#define LEFT ((i+NUMBER_OF_PHILOSOPHERS-1)%NUMBER_OF_PHILOSOPHERS)
#define RIGHT ((i+1)%NUMBER_OF_PHILOSOPHERS)
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[NUMBER_OF_PHILOSOPHERS];
sem_t mutex;
sem_t sem[NUMBER_OF_PHILOSOPHERS];

void think(){
	sleep(5);
}

void eat(){
	sleep(5);
}

void test(int i){
	if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
		state[i] = EATING;
		sem_post(&sem[i]);
	}
}

void takeForks(int i){
	sem_wait(&mutex);
	state[i] = HUNGRY;
	test(i);
	sem_post(&mutex);
	sem_wait(&sem[i]);
}

void putForks(int i){
	sem_wait(&mutex);
	state[i] = THINKING;
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
}


void *philosopher(void *arg) {
	int id = *(int *)arg;
	while(1){
		think();
		takeForks(id);
		eat();
		putForks(id);
	}
}

int main(void){
	pthread_t threads[NUMBER_OF_PHILOSOPHERS];
	int *id[NUMBER_OF_PHILOSOPHERS];
	sem_init(&mutex, 0, 1);


	// allocate the memory
	for(int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++){
		id[i] = malloc(sizeof(int));
		*id[i] = i;
		state[i] = THINKING;
	}

	for(int x = 0; x < NUMBER_OF_PHILOSOPHERS; x++){
		sem_init(&sem[x], 0, 0);
		pthread_create(&threads[x], NULL, philosopher, id[x]);
	}

	while(1){
		for(int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++){
			printf("%s ",((state[i] == HUNGRY) ? "HUNGRY" : ((state[i] == THINKING) ? "THINKING" : "EATING") ) );
		}
		printf("\n");
	}

	for(int z = 0; z < NUMBER_OF_PHILOSOPHERS; z++){
		pthread_join(threads[z], NULL);	
	}

	return 0;
}












































