#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

void ForEach(std::vector<int>& values, std::function<void(int)> func)
{
	for (int value : values)
		func(value);
}

int main()
{
	std::vector<int> values = { 1,2,3,4 };
	auto it = std::find_if(values.begin(), values.end(), [](int value) { return value > 3; });
	std::cout << *it << std::endl;
	std::cin.get();
	return 0;
}


