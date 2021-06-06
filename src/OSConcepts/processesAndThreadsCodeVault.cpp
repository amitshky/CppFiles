#include <iostream>
#include <unistd.h>
#include <pthread.h>

void* Routine(void* i)
{
	printf("hello from threads. Process id %d\n", getpid()); // you get same pid for threads
	// processes can contain multiple threads // but not vice versa
}

int main(int argc, char* argv[])
{
	// about processes
	//int id = fork(); // returns id of the child process
	//printf("Hello World! from %d\n", id);
	//if (id == 0)
	//	printf("Child process! id = %d\n", id);
	//else if (id == -1)
	//	printf("Error!!!\n");
	//else
	//	printf("Parent process! id = %d\n", id);
	// no. of fork() calls => n => 2^n processes
	// if we want to create only 3 processes for example
	// we only fork on the main process
	//if (id > 0)
	//	fork();
	//printf("hello world\n");

	// about threads
	pthread_t t1, t2;
	if (pthread_create(&t1, NULL, &Routine, NULL))
		return 1;
	if (pthread_create(&t2, NULL, &Routine, NULL))
		return 2;
	if (pthread_join(t1, NULL))
		return 3;
	if (pthread_join(t2, NULL))
		return 4;


	std::cin.get();
	return 0;
}
