/**
 * Future
 * - provides mechanism to access the result of asynchronous operations
 * - we can multithread without using std::thread
 * - asynchronous operation (created via std::async, std::packaged_task, or std::promise) can provide a std::future
 *   object to the creator of that asynchronous operation
 *   - std::async will create an asynchronous task and return a std::future
 * - std::future is a structure pointing to a result that will be computed in the future
 * 
 * - get() function on a future will wait until the result is available and return ths result once it is
 * - we cannont call get() several times on the same future
 *   - in other words get() consumes the result
 * - the return type of the future is std::future<DatatypeOfLabmda>
 * 
 * - wait() doesn't consume the result
 * - we can wait for several futures and consume their result together
 * - wait_for(duration) wait_until(timepoint)
 * 
 * - bool valid() => after get() is used valid() returns false
 * 
 */

#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>

using namespace std::literals::chrono_literals;

int main()
{
	//auto f1 = std::async(std::launch::async, []() {
	//	std::this_thread::sleep_for(9s);
	//	return 9;
	//});

	//auto f2 = std::async(std::launch::async, []() {
	//	std::this_thread::sleep_for(6s);
	//	return 6;
	//});

	//auto f3 = std::async(std::launch::async, []() {
	//	std::this_thread::sleep_for(3s);
	//	return 3;
	//});

	//auto timeout = std::chrono::milliseconds(10);
	//
	//while (f1.valid() || f2.valid() || f3.valid())
	//{
	//	if (f1.valid() && f1.wait_for(timeout) == std::future_status::ready)
	//		std::cout << "Task 1 done! " << f1.get() << std::endl;

	//	if (f2.valid() && f2.wait_for(timeout) == std::future_status::ready)
	//		std::cout << "Task 2 done! " << f2.get() << std::endl;

	//	if (f3.valid() && f3.wait_for(timeout) == std::future_status::ready)
	//		std::cout << "Task 3 done! " << f3.get() << std::endl;

	//	std::cout << "I'm doing my own work!" << std::endl;
	//	std::this_thread::sleep_for(1s);
	//	std::cout << "I'm done with my own work!" << std::endl;
	//}

	//std::cout << "Everything is done!" << std::endl;


	// passing parameters to async
	std::vector<std::future<size_t>> futures;

	for (size_t i = 0; i < 10; i++)
	{
		futures.emplace_back(std::async(std::launch::async, [](size_t param) {
			std::this_thread::sleep_for(std::chrono::seconds(param));
			return param;
		}, i));
	}

	std::cout << "Start querying" << std::endl;

	for (auto& f : futures)
		std::cout << f.get() << std::endl;
		
	std::cin.get();
	return 0;
}
