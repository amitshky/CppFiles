#include <iostream>

int main()
{
	int a = 120;
	for (int i = 0; i < 180; ++i)
	{
		std::cout << a + i << ',';
	}
	std::cout << '\n';
}