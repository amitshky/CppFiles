/**
 * std::vector<type>
 * 
 * Dynamic array
 * * this is achieved by allocating a new memory block which is greater than the original block
 * 
 * size (number of elements) and capacity (actually allocated memory)
 * 
 * Functions:
 * * size(), capacity(), max_size()
 * * empty(): test whether the vector is empty
 * * reserve(): request a change in capacity
 * * shrink_to_fit(): C++11; may cause reallocation
 * * resize(): changes size()
 * 
 * Modifiers:
 * * insert(): inserts element before the position specified
 * * push_back(): inserts an element at the back of the vector
 * * pop_back(): removes an element from the back of the vector
 * * emplace(): C++11; Construct and instert element
 * * emplace_back(): C++11; Construct and instert element at the end
 * * swap()
 * * erase(): erase element
 * * clear(): clears the entire vector
 * 
 * Element access:
 * * []: this is not safe, can access out of bounds elements 
 * * at(): safer, bounded
 * * front()
 * * back()
 * * data(): C++11; gives the pointer to the element
 * 
 * Iterators:
 * * begin(): iterator to the beginning
 * * end(): iterator to the end
 * * rbegin(): iterator to the reverse beginning
 * * rend(): iterator to the reverse end
 * * cbegin(), cend(), crbegin(), crend(): const iterators
 **/

#include <iostream>
#include <vector>

int main()
{
	std::vector<int32_t> vec;

	// Declarations
#if 0
	std::vector<int32_t> vec1;
	std::vector<int32_t> vec2(5, 123); // allocate capacity (size) of 5 and initialize all the elements with 123
	std::vector<int32_t> vec3 = { 1, 2, 3, 4, 5 }; // initializer list
	std::vector<int32_t> vec4{ 1, 2, 3, 4, 5 };    // uniform initialization
#endif

	// this is bad cuz it will constantly allocate memory (if the vector is full)
	// unnecessary copy and allocation if you already know the total number elements
	// so it is better to reserve a block of memory
	vec.reserve(6);
	for (int32_t i = 0; i < 7; i++)
	{
		vec.push_back(i);
		std::cout << "Size = " << vec.size() << " Capacity = " << vec.capacity() << '\n';
	}
	std::cout << "---------------\n";

	vec.shrink_to_fit(); // makes capacity equal to size() // may cause reallocation
	std::cout << "Size = " << vec.size() << " Capacity = " << vec.capacity() << '\n';
	std::cout << "---------------\n";

	auto it = vec.emplace(vec.cbegin() + 2, 111); // returns iterator where the element was inserted
	vec.emplace(it + 5, 222); // constructs and inserts at the 5th position from the `it` iterator 
	vec.emplace_back(333);    // consturcts and inserts at the end
	vec.insert(vec.cbegin(), 444); // inserts before `begin()` i.e., before 0
	vec.erase(vec.cbegin() + 2);   // removes the 3rd element i.e., 1

	for (auto& v : vec)
		std::cout << v << '\n';
	std::cout << "Size = " << vec.size() << " Capacity = " << vec.capacity() << '\n';
	std::cout << "---------------\n";
}