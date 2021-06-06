#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>

#define NUM_THREADS 8
#define CAPACITY    10

int buffer[CAPACITY];
int count = 0;

sem_t semEmpty;
sem_t semFull;
pthread_mutex_t mutexVar;


void* Producer(void* args)
{
	while (1)
	{
		// produce item
		// the produced item should not go to waste
		int item = rand() % 100;
		sleep(1); // indicates that production took some time

		// insert into buffer
		sem_wait(&semEmpty);
		pthread_mutex_lock(&mutexVar);
		buffer[count] = item;
		count++;
		pthread_mutex_unlock(&mutexVar);
		sem_post(&semFull);
	}
}

void* Consumer(void* args)
{
	while (1)
	{
		int item = -1; // -1 is consumed if the buffer is empty // this should not happen

		// remove from buffer
		sem_wait(&semFull);
		pthread_mutex_lock(&mutexVar);
		item = buffer[count - 1];
		count--;
		pthread_mutex_unlock(&mutexVar);
		sem_post(&semEmpty);
	
		// consume item
		printf("Consumed %d\n", item);
		sleep(0.1); // indicates that the consumption took some time
	}
}

int main()
{
	srand(time(nullptr));
	pthread_t th[NUM_THREADS];

	pthread_mutex_init(&mutexVar, nullptr);
	sem_init(&semEmpty, 0, CAPACITY);
	sem_init(&semFull,  0, 0);
	
	for (int i = 0; i < NUM_THREADS; i++)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&th[i], nullptr, &Producer, nullptr) != 0)
				perror("Error creating thread\n");
		}
		else
		{
			if (pthread_create(&th[i], nullptr, &Consumer, nullptr) != 0)
				perror("Error creating thread\n");
		}
	}

	for (int i = 0; i < NUM_THREADS; i++)
	{
		if (i % 2 == 0)
		{
			if (pthread_join(th[i], nullptr) != 0)
				perror("Error joining thread\n");
		}
		else
		{
			if (pthread_join(th[i], nullptr) != 0)
				perror("Error joining thread\n");
		}
	}

	sem_destroy(&semEmpty);
	sem_destroy(&semFull);
	pthread_mutex_destroy(&mutexVar);
	std::cin.get();
	return 0;
}
