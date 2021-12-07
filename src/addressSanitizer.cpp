/**
 * Address Sanitizer detects memory corruption bugs such as buffer overflows or accesses to a dangling pointer
 **/

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<int> list{ 1, 3, 4 };
	auto three = std::find(list.begin(), list.end(), 3);
	
	for (int i = 0; i < 100; i++)
		list.push_back(i); // this will reallocate the vector when the capacity is full, making the `three` iterator invalid

	std::cout << *three << '\n';
}