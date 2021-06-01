/**
 * ADVANCED LOCKING
 * 
 * Recursive locking
 * - A thread cannot acquire the same mutex twice
 * - A calling thread must not own the mutex prior to calling lock or try_lock.
 * - if we used std::mutex then the lock gets set in Both() and again in Mult() by the same thread causing deadlock
 * - we can use std::recursive_mutex
 * - A calling thread owns a recursive_mutex for a period of time that starts when it successfully calls 
 *   either lock or try_lock. During this period, the thread may make additional calls to lock or try_lock.
 *   The period of ownership ends when the thread makes a matching number of calls to unlock.
 * 
 * Timed locking
 * - if you don't want a thread to wait for ever for another thread to unlock the mutex we can use 
 *   std::timed_mutex and std::timed_recursive_mutex
 * - lock() unlock() try_lock_for() try_lock_until()
 * - timed_mutex provides the ability to attempt to claim ownership of a timed_mutex with a timeout via the try_lock_for() 
 *   and try_lock_until() methods.
 * - try_lock_for() allows us to set a timeout after when the function automatically returns even if the lock was not acquired
 * - returns true if the lock has been acquired and false otherwise
 * 
 * Call once
 * - to call a function only once no matter the number of threads that are used
 * - An object of type std::once_flag that is passed to multiple calls to std::call_once allows those calls to 
 *   coordinate with each other such that only one of the calls will actually run to completion.
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// Recursive Locking
class Complex
{
public:
	Complex() :i(0) {};

	void Mult(int x)
	{
		std::lock_guard<std::recursive_mutex> lock(m_Mutex);
		i *= x;
	}

	void Div(int x)
	{
		std::lock_guard<std::recursive_mutex> lock(m_Mutex);
		i /= x;
	}

	void Both(int x, int y)
	{
		std::lock_guard<std::recursive_mutex> lock(m_Mutex);
		Mult(x);
		Div(y);
	}

public:
	int i;

private:
	std::recursive_mutex m_Mutex;
};

// Timed Locking
static bool s_Finished = false;
std::timed_mutex g_TimedMutex;

using namespace std::literals::chrono_literals;

void Work()
{
	//std::chrono::milliseconds timeout(100);
	while (!s_Finished)
	{
		if (g_TimedMutex.try_lock_for(200ms)) // the thread waits for certain time for the mutex to be unlocked
		{
			std::cout << std::this_thread::get_id() << ": do work with mutex" << std::endl;

			std::chrono::milliseconds sleepDuration(250);
			std::this_thread::sleep_for(sleepDuration);

			g_TimedMutex.unlock();

			std::this_thread::sleep_for(sleepDuration);
		}
		else
		{
			std::cout << std::this_thread::get_id() << ": do work without mutex" << std::endl;

			//std::chrono::milliseconds sleepDuration(100);
			std::this_thread::sleep_for(300ms);
		}
	}
}

// Call once
std::once_flag g_OnceFlag;
void DoSomething()
{
	std::call_once(g_OnceFlag, []() { std::cout << "Called once" << std::endl; });
	std::cout << "Called each time" << std::endl;
}

int main()
{
	// Timed locking
	std::thread t1(Work);
	std::thread t2(Work);

	std::cin.get();
	s_Finished = true;

	t1.join();
	t2.join();

	// Call once
	//std::thread t1(DoSomething);
	//std::thread t2(DoSomething);
	//std::thread t3(DoSomething);
	//std::thread t4(DoSomething);

	//t1.join();
	//t2.join();
	//t3.join();
	//t4.join();

	std::cin.get();
	return 0;
}
