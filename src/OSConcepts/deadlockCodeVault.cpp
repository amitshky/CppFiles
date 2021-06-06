#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 4

pthread_mutex_t fuelMutex;
pthread_mutex_t waterMutex;

int fuel  = 50;
int water = 10;

void* Routine(void* i)
{
	// the order of mutex lock is different
	// if one thread locks fuel mutex and other thread locks water mutex
	// since both are waiting for the other thread to unlock the mutex, deadlock occurs
	if (rand() % 2 == 0) // this isnt something tht you normally do but it is done to immitate a large codebase
	{
		pthread_mutex_lock(&fuelMutex);
		//sleep(1); // uncomment to see deadlock
		pthread_mutex_lock(&waterMutex);
	}
	else
	{
		pthread_mutex_lock(&waterMutex);
		//sleep(1); // uncomment to see deadlock
		pthread_mutex_lock(&fuelMutex);
	}
	fuel += 50;
	water = fuel;
	printf("Fuel increment = %d, water increment = %d\n", fuel, water);
	pthread_mutex_unlock(&fuelMutex);
	pthread_mutex_unlock(&waterMutex);
}

int main(int argc, char* argv[])
{
	pthread_t t[NUM_THREADS];
	pthread_mutex_init(&fuelMutex, NULL);
	pthread_mutex_init(&waterMutex, NULL);

	for (int i = 0; i < NUM_THREADS; i++)
	{
		if (pthread_create(&t[i], NULL, &Routine, NULL))
			perror("Thread creation failed!\n");
	}

	for (int i = 0; i < NUM_THREADS; i++)
	{
		if (pthread_join(t[i], NULL))
			perror("Thread join failed!\n");
	}

	printf("Fuel = %d, Water = %d\n", fuel, water);

	pthread_mutex_destroy(&fuelMutex);
	pthread_mutex_destroy(&waterMutex);

	//getchar();
	return 0;
}
