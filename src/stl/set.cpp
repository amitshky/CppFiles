/**
 * std::set<Type>
 * 
 * 1. Associative container that contains a "sorted" set of unique objects
 * 2. Implemented using Red-black tree
 * 3. Insertion, removal and search has logarithmic complexity
 * 4. Storing user defined types in std::set requires a compare function
 * 5. We can also pass the order for sorting
 *    std::set<type, std::greater<>/std::less<>>
 **/

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <functional> // for std::greater and std::less

class Book
{
public:
	Book(int32_t year, const std::string& title)
		:year(year), title(title) {}

	// overloading comparision operators for std::set
	inline bool operator< (const Book& other) const { return year < other.year; }
	inline bool operator> (const Book& other) const { return year > other.year; }

	friend std::ostream& operator<< (std::ostream& stream, const Book& book);

public:
	int32_t year;
	std::string title;
};

std::ostream& operator<< (std::ostream& stream, const Book& book)
{
	stream << book.year << ": " << book.title;
	return stream;
}

int main()
{
	std::set<int32_t> nums = { 1, 2, 3, 4, 5, 1, 2, 3 };
	for (auto& n : nums)
		std::cout << n << '\n';

	std::set<Book, std::greater<Book>> books = { 
		{ 1998, "A Clash of Kings" }, 
		{ 2011, "A Dance with Dragons" }, 
		{ 1996, "A Game of Thrones" }, 
		{ 2005, "A Feast for Crows" }, 
		{ 2000, "A Storm of Swords" }, 
		{ 2005, "Some book" } // this will be omitted
	};

	for (auto& b : books)
		std::cout << b << '\n';
}