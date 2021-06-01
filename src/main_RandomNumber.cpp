#include <iostream>
#include <random>

int main()
{
	std::random_device device; // produces uniformly distributed 32bit integers 
		// through OS entropy pool
		// should not be used repeatedly
		// so we use this to get a single random number 
		// which is used as a seed for the PRNG
	std::mt19937 generator(device()); // Mersene Twister PRNG
		// initialized by the seed produced by the device
		// std::mt19937_64 for 64 bit PRNG
	std::uniform_int_distribution<int> distInt(0, 99);
	std::uniform_real_distribution<float> distFloat(0, 1);

	for (int i = 0; i < 100; i++)
		//std::cout << distInt(generator) << std::endl;
		std::cout << distFloat(generator) << std::endl;


	std::cin.get();
	return 0;
}