/**
 * Atomic Types
 * - main advantage is performance
 * - in most cases std::atomic operations are implemented with lock-free operations
 * - for intergral types like int, float,... lock-free implementations are used but for big types mutexes might be used
 * - store() and load() functions => set and get contents of std::atomic
 * - also exchange() => sets the atomic to a new value and returns the value held previously
 * - compare_exchange_weak() and compare_exchange_strong() => performs atomic exchange only if the value is equal 
 *   to provided expected value
 * - for all integral types std::atomic provides member functions like operators++, --, fetch_add, fetch_sub, ...
 * 
 * Atomic Operation
 * - (CppCon2017: Fedor Pikus)
 * - operation that is guaranteed to run in a single transaction
 * - at the low level they are hardware instructions
 */

#include <iostream>
#include <thread>
#include <atomic>

class Counter
{
public:
	Counter() :m_Value(0) {}

	inline void Increment()
	{
		m_Value++;
	}

	inline void Decrement()
	{
		m_Value--;
	}

	inline int GetValue() const { return m_Value.load(); }

private:
	std::atomic<int> m_Value;
};

int main()
{
	Counter counter;
	std::thread t1([&counter]() { counter.Increment(); });
	std::thread t2([&counter]() { counter.Increment(); });
	std::thread t3([&counter]() { counter.Decrement(); });

	t1.join();
	t2.join();
	t3.join();

	std::cout << counter.GetValue() << std::endl;

	std::cin.get();
	return 0;
}
