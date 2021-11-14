/**
 * std::multiset<Type, Compare>
 * 
 * 1. Associative container that can contain a sorted set of duplicate objects
 * 2. Implemented as a Red-black tree
 * 3. Insertion, Removal and Search have logarithmic complexity
 * 4. Storing user defined types in std::set requires a compare function
 * 5. We can also pass the order for sorting
 *    std::set<type, std::greater<>/std::less<>>
 * 
 * Iterators:
 * * begin(), cbegin(), end(), cend(), rbegin(), crbegin(), rend(), crend()
 * 
 * Capacity:
 * * empty(), size(), max_size()
 * 
 * Modifiers:
 * * clear(), insert(), emplace(), erase(), swap()
 * * emplace_hint(): constructs elements in-place with hint
 * * extract(): extract nodes fron the container
 * * merge(): merge nodes fron other container
 * 
 * Lookup:
 * * find(), count(), contains()
 **/

#include <iostream>
#include <set>
#include <string>
#include <functional>

class Book
{
public:
	Book(int32_t year, const std::string& title)
		: year(year), title(title) {}

	inline bool operator< (const Book& other) const { return year < other.year; }
	inline bool operator> (const Book& other) const { return year > other.year; }

	friend std::ostream& operator<< (std::ostream& stream, const Book& book)
	{
		stream << book.year << ": " << book.title;
		return stream;
	}
	
public:
	int32_t year;
	std::string title;
};

int main()
{
	std::multiset<int32_t> multiSet = { 1, 2, 3, 4, 5, 1, 3, 5 };

	for (auto& m : multiSet)
		std::cout << m << '\n';
	std::cout << "------------------\n";

	std::multiset<Book, std::greater<Book>> books = { 
		{ 1998, "A Clash of Kings" }, 
		{ 2011, "A Dance with Dragons" }, 
		{ 1996, "A Game of Thrones" }, 
		{ 2005, "A Feast for Crows" }, 
		{ 2000, "A Storm of Swords" }, 
		{ 2005, "The Book Thief" } // this won't be omitted unlike std::set
	};

	books.emplace(Book(2006, "some book"));
	books.emplace_hint(books.begin(), 2007, "someother book");

	for (auto& b : books)
		std::cout << b << '\n';

	Book AGOT(1996, "A Game of Thrones");
	if (books.find(AGOT) != books.end())
		std::cout << "Book found\n";
}