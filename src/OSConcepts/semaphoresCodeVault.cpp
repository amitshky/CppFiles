#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4

sem_t semaphore;

void* Routine(void* i)
{
	sem_wait(&semaphore); // only one thread can access this part of the code at a time 
	/**
	 * P(s):
	 * if s == 0
	 *    wait
	 * if s > 0
	 *    s--
	 */
	sleep(1);
	printf("Hello from thread %d\n", *(int*)i);
	sem_post(&semaphore);
	/**
	 * V(s):
	 * s++
	 */
	free(i);
}

int main(int argc, char* argv[])
{
	pthread_t t[NUM_THREADS];
	//       pointer to sem   param   initial value
	sem_init(&semaphore,      0,      1); // param  0 => if multiple threads // 1 => if multiple processes

	for (int i = 0; i < NUM_THREADS; i++)
	{
		int* a = (int*)malloc(sizeof(int));
		*a = i;
		if (pthread_create(&t[i], NULL, &Routine, a))
			perror("Failed to create thread\n");
	}

	for (int i = 0; i < NUM_THREADS; i++)
	{
		if (pthread_join(t[i], NULL))
			perror("Failed to join thread\n");
	}

	sem_destroy(&semaphore);

	std::cin.get();
	return 0;
}
