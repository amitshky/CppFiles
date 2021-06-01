#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

template<typename Iter>
void MergeSort(Iter first, Iter last)
{
	if (last - first > 1)
	{
		Iter middle = first + (last - first) / 2;
		MergeSort(first, middle);
		MergeSort(middle, last);
		std::inplace_merge(first, middle, last);
	}
}

template<typename T>
void Print(const std::vector<T>& values)
{
	for (auto& value : values)
		std::cout << value << std::endl;
}

int main()
{
	std::vector<int> collection = { 11,7,4,9,2,3,0,12,45,22,6,25 };
	std::vector<int> collection2 = { 2, 4, 4, 5, 7, 15 };
	// is any number divisible by 3
	bool div3 = std::any_of(collection.begin(), collection.end(), [](int x) { return x % 3 == 0; });
	// count how many numbers are even
	int count = std::count_if(collection.begin(), collection.end(), [](int x) { return x % 2 == 0; });
	
	auto itr = std::find_if(collection.begin(), collection.end(), [](int x) { return x % 2 == 0; });

	// finds the nth element in O(n)
	auto median_pos = collection.begin() + collection.size() / 2;
	std::nth_element(collection.begin(), median_pos, collection.end());
	std::cout << *median_pos << std::endl;
	std::cout << "----------------" << std::endl;

	std::mt19937 generator(0);
	std::shuffle(collection.begin(), collection.end(), generator);
	Print(collection);
	std::cout << "----------------" << std::endl;

	MergeSort(collection.begin(), collection.end());
	Print(collection);
	std::cout << "----------------" << std::endl;

	// merges two sorted collections; the resultant collection is also sorted
	std::vector<int> result;
	std::sort(collection.begin(), collection.end());
	std::merge(collection.begin(), collection.end(), collection2.begin(), collection2.end(), std::back_inserter(result));
	Print(result);
	std::cout << "----------------" << std::endl;

	// std::find
	int arr[] = { 1, 2, 3, 4, 5 };
	int* p = std::find(arr, arr + 5, -1);

	if (p != arr + 5)
		std::cout << "Element found" << std::endl;
	else
		std::cout << "Element not found" << std::endl;
	std::cout << "----------------" << std::endl;

	std::cin.get();
	return 0;
}
