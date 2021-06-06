#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

#define LEFT  (self + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (self + 1) % NUM_PHILOSOPHERS

#define THINKING 0
#define HUNGRY   1
#define EATING   2

int state[NUM_PHILOSOPHERS] = { 0 };

sem_t semPhils[NUM_PHILOSOPHERS];
pthread_mutex_t mutPhil;


void Test(int self)
{
	if (state[self] = HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
	{
		state[self] = EATING;
		sleep(1);
		sem_post(&semPhils[self]);
	}
}

void TakeForks(int self)
{
	pthread_mutex_lock(&mutPhil);
	state[self] = HUNGRY;
	Test(self); // try to acquire 2 forks
	pthread_mutex_unlock(&mutPhil);
	sem_wait(&semPhils[self]);
}

void PutForks(int self)
{
	pthread_mutex_lock(&mutPhil);
	state[self] = THINKING;
	sleep(0.3);
	Test(LEFT);  // see if left neighbour can now eat
	Test(RIGHT); // see if right neighbour can now eat
	pthread_mutex_unlock(&mutPhil);
}

void* Philosopher(void* self)
{
	while (1)
	{
		// think
		printf("Philosopher %d thinking\n", (int64_t)self);
		TakeForks((int64_t)self);
		// eat
		printf("Philosopher %d eating\n", (int64_t)self);
		PutForks((int64_t)self);
	}
}

int main()
{
	pthread_t th[NUM_PHILOSOPHERS];
	pthread_mutex_init(&mutPhil, nullptr);
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
		sem_init(&semPhils[i], 0, 0);

	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		if (pthread_create(&th[i], nullptr, &Philosopher, (void*)i) != 0)
			perror("Error creating thread\n");
	}

	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		if (pthread_join(th[i], nullptr) != 0)
			perror("Error joining thread\n");
	}

	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
		sem_destroy(&semPhils[i]);
	pthread_mutex_destroy(&mutPhil);
	std::cin.get();
	return 0;
}
