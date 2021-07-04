#include <iostream>

int main()
{
	uint64_t i = 0;
	for (i = 0; i < ~0ULL; i++);
	std::cout << i << '\n';
}