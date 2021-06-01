/**
 * https://baptiste-wicht.com/categories/c%2B%2B11-concurrency-tutorial.html
 */

#include <iostream>
#include <thread>
#include <vector>

int main()
{
	std::vector<std::thread> threads;
	for (int i = 0; i < 5; i++)
		threads.push_back(std::thread([]() {
			std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
		}));

	for (auto& t : threads)
		t.join();

	std::cin.get();
	return 0;
}