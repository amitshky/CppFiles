#include <iostream>
#include <pthread.h>

int mails = 0;
//int lockVar = 0; // for mutex example
pthread_mutex_t mutex;

void* Routine(void* i)
{
	for (int i = 0; i < 1000000; i++)
	{
		//if (lockVar == 1) // mutex example
		//	// wait until lockVar = 0
		//lockVar = 1; // mutex example
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		//lockVar = 0; // mutex example
	}
}

int main(int argc, char* argv[])
{
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL); // initializing mutex
	if (pthread_create(&t1, NULL, &Routine, NULL))
		return 1;
	if (pthread_create(&t2, NULL, &Routine, NULL))
		return 2;
	if (pthread_join(t1, NULL))
		return 3;
	if (pthread_join(t2, NULL))
		return 4;
	pthread_mutex_destroy(&mutex);
	printf("number of mails: %d", mails);

	std::cin.get();
	return 0;
}
