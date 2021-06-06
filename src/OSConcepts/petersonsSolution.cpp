#include <cstdio> 
#include <cstdlib>
#include <pthread.h> 

constexpr int MAX = 100;
int flag[2]; // indicates which process is interested in entering critical region
int turn;
int ans = 0;

void LockInit() 
{
	// Initialize lock by reseting the desire of both the threads to acquire the locks. 
	// And, giving turn to one of them. 
	flag[0] = flag[1] = 0; 
	turn = 0; 
}

// Executed before entering critical section 
void Lock(int self) 
{ 
	// Set flag[self] = 1 saying you want to acquire lock 
	flag[self] = 1; 
  
	// But, first give the other thread the chance to acquire lock 
	turn = 1 - self; 
  
	// Wait until the other thread looses the desire to acquire lock or it is your turn to get the lock. 
	while (flag[1 - self] == 1 && turn == 1 - self); 
}

// Executed after leaving critical section 
void Unlock(int self) 
{
	// You do not desire to acquire lock in future. 
	// This will allow the other thread to acquire the lock. 
	flag[self] = 0; 
} 

void* Routine(void* self) 
{
	printf("Thread Entered: %d\n", (int64_t)self); 
  
	Lock((int64_t)self);
	// Critical section (Only one thread can enter here at a time) 
	for (int i = 0; i < MAX; i++)
	{
		ans++;
		printf("from thread  %d printing...... %d\n", (int64_t)self, i);
	}
	Unlock((int64_t)self);
}

int main()
{ 
	// Initialized the lock then fork 2 threads 
	pthread_t p1, p2; 
	LockInit(); 
 
	// Create two threads (both run func)
	pthread_create(&p1, NULL, Routine, (void*)0);
	pthread_create(&p2, NULL, Routine, (void*)1);
 
	// Wait for the threads to end. 
	pthread_join(p1, NULL); 
	pthread_join(p2, NULL); 
 
	printf("Actual Count: %d | Expected Count: %d\n", ans, MAX * 2);
 
	//getchar();
	return 0; 
}
