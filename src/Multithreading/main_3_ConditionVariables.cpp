/**
 * Condition variables
 * - manages a list of threads waiting until another thread notifies them
 * - each thread that wants to wait on the condition variable has to acquire a lock (std::mutex) first
 * - the lock is then released when the thread starts to wait on the condition and the lock is 
 *   acquired again when the thread is awakened
 * -std::unique_lock is necessary in condition variables
 * 
 * Bounded buffer is a cyclic buffer with a certain capacity with a start and an end
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

class BoundedBuffer
{
public:
	BoundedBuffer(int capacity)
		: m_Capacity(capacity), m_Front(0), m_Rear(0), m_Count(0)
	{
		m_Buffer = new int[capacity];
	}

	~BoundedBuffer()
	{
		delete[] m_Buffer;
	}

	void Deposit(int data)
	{
		std::unique_lock<std::mutex> lock(m_Lock);
		m_NotFull.wait(lock, [this]() { return m_Count != m_Capacity; }); // the condition must return false to continue waiting

		m_Buffer[m_Rear] = data;
		m_Rear = (m_Rear + 1) % m_Capacity;
		m_Count++;

		lock.unlock(); // also done automatically by destructor of unique_lock. So not necessary
		m_NotEmpty.notify_one();
	}

	int Fetch()
	{
		std::unique_lock<std::mutex> lock(m_Lock);
		m_NotEmpty.wait(lock, [this]() { return m_Count != 0; });

		int result = m_Buffer[m_Front];
		m_Front = (m_Front + 1) % m_Capacity;
		m_Count--;

		lock.unlock();
		m_NotFull.notify_one();

		return result;
	}

private:
	int* m_Buffer;
	int m_Capacity;

	int m_Front, m_Rear, m_Count;

	std::mutex m_Lock;
	std::condition_variable m_NotFull;
	std::condition_variable m_NotEmpty;
};

using namespace std::literals::chrono_literals;

void Consumer(int id, BoundedBuffer& buffer)
{
	for (int i = 0; i < 5; i++)
	{
		int value = buffer.Fetch();
		std::cout << "Consumer: " << id << " Fetched " << value << std::endl;
		std::this_thread::sleep_for(250ms);
	}
}

void Producer(int id, BoundedBuffer& buffer)
{
	for (int i = 0; i < 8; i++)
	{
		buffer.Deposit(i);
		std::cout << "Producer: " << id << " produced " << i << std::endl;
		std::this_thread::sleep_for(100ms);
	}
}

int main()
{
	BoundedBuffer buffer(10);

	std::thread c1(Consumer, 0, std::ref(buffer)); // std::ref to avoid copy
	std::thread c2(Consumer, 1, std::ref(buffer));
	std::thread c3(Consumer, 2, std::ref(buffer));
	std::thread p1(Producer, 0, std::ref(buffer));
	std::thread p2(Producer, 1, std::ref(buffer));

	c1.join();
	c2.join();
	c3.join();
	p1.join();
	p2.join();

	std::cin.get();
	return 0;
}
