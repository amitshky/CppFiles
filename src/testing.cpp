#include <iostream>
#include <bitset>

int main()
{
	float num = -1.1f;
	long bits = *(long*)&num;
	std::cout << std::bitset<32>(bits) << '\n';

	float num2 = *(float*)&bits;
	std::cout << num2 << '\n';
}
