/**
 * Mutex
 * - A calling thread owns a mutex from the time that it successfully calls either lock() or try_lock() until it calls unlock.
 * - When a thread owns a mutex, all other threads will block (for calls to lock()) or receive a false return value (for try_lock()) 
 *   if they attempt to claim ownership of the mutex.
 * - A calling thread must not own the mutex prior to calling lock() or try_lock().
 * - The behavior of a program is undefined if a mutex is destroyed while still owned by any threads, 
 *   or a thread terminates while owning a mutex
 * 
 * synchronizing threads using mutex
 * keep in mind that locks are slow
 */

#include <iostream>
#include <vector>
#include <string>

#include <thread>
#include <mutex>

class Counter
{
public:
	Counter() :value(0) {}

	void Increment()
	{
		++value;
	}

	void Decrement()
	{
		if (value == 0)
			throw "Value should not be less than 0!";
		--value;
	}

public:
	int value;
};

// wrapper for Counter with locks
class ConcurrentCounter
{
public:
	ConcurrentCounter() = default;

	void Increment()
	{
		m_Mutex.lock();
		counter.Increment();
		m_Mutex.unlock();
	}

	void Decrement()
	{
		m_Mutex.lock();
		/**
		 * When exception occurs the unlock() function is not called
		 * and the lock is left in block state
		 * so we use try-catch block
		 * we unlock the lock before throwing the exception
		 */
		try
		{
			counter.Decrement();
		}
		catch (const std::string& e)
		{
			m_Mutex.unlock();
			throw e;
		}
		m_Mutex.unlock();
	}

public:
	Counter counter;

private:
	std::mutex m_Mutex;
};

/**
 * suppose we have 10 different exit points (throws and catches) in the ConcurrentCounter struct
 * the code starts to look ugly, and there is a chance that we might forget to call unlock() from one the exit points 
 * to solve this we can use std::lock_guard() to automatically manage locks
 */
class ConcurrentSafeCounter
{
public:
	ConcurrentSafeCounter() = default;

	void Increment()
	{
		std::lock_guard<std::mutex> guard(m_Mutex);
		counter.Increment();
	}

	void Decrement()
	{
		std::lock_guard<std::mutex> guard(m_Mutex);
		counter.Decrement();
	}
	
public:
	Counter counter;

private:
	std::mutex m_Mutex;
};

int main()
{
	ConcurrentSafeCounter counter;
	std::vector<std::thread> threads;

	for (int i = 0; i < 5; i++)
	{
		threads.push_back(std::thread([&counter]() {
			for (int i = 0; i < 100; i++)
				counter.Decrement();
		}));
	}

	for (auto& t : threads)
		t.join();

	std::cout << "Counter = " << counter.counter.value << std::endl;

	std::cin.get();
	return 0;
}