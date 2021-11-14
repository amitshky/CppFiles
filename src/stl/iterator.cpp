/**
 * Iterators point to memory addresses of STL containers
 **/

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <unordered_map>

template <typename Iterator>
void PrintList(const Iterator first, const Iterator last)
{
	for (Iterator it = first; it != last; it++)
		std::cout << *it << "\n";
}

// iterator traits' value_type gives the type stored in the container, this requires 'typename' keyword in front
template <typename Iterator>
typename std::iterator_traits<Iterator>::value_type Sum(const Iterator first, const Iterator last)
{
	using containerType = typename std::iterator_traits<Iterator>::value_type;
	containerType result = 0;
	
	for (Iterator it = first; it != last; it++)
		result += *it;

	return result;
} 

int main()
{
	std::vector<int32_t> vec{ 1, 2, 3, 5, 6, 78, 90, 33, 7 };
	std::unordered_map<std::string, int32_t> map;
	map["hello"] = 0;
	map["how"] = 1;
	map["are"] = 2;
	map["you"] = 4;
	
	for (auto& [key, value] : map)
	{
		std::cout << key << ": " << value << "\n";
	}
	std::cout << "___________________________\n";

	// iterating over a container like unordered map, which has 2 values 
	for (std::unordered_map<std::string, int32_t>::iterator it = map.begin(); it != map.end(); it++)
	{
		auto& key   = it->first;
		auto& value = it->second;

		std::cout << key << ": " << value << "\n";
	}
	std::cout << "___________________________\n";

	PrintList(vec.begin(), vec.end());
	std::cout << "___________________________\n";

	std::cout << Sum(vec.begin(), vec.end()) << "\n";
	std::cout << "___________________________\n";
}