/**
 * std::unordered_set<Type, Hash>
 * 
 * 1. Unordered set of associative container that contains unique objects
 * 2. Search, insertion, and removal have constant time complexity
 * 3. Uses hashing to insert elements into buckets, the elements are internally organized into buckets
 * 4. Fast access to elements
 * 6. To use user-defined datatype as key, you need a hash function, and a comparision function for equality
 * 
 * Iterators:
 * * begin(), cbegin(), end(), cend()
 * 
 * Capacity:
 * * empty(), size(), max_size()
 * 
 * Element access:
 * [], at() // C++11
 * 
 * Modifiers:
 * * clear(), insert(), erase(), swap(), emplace(), emplace_hint()
 * 
 * Element lookup:
 * * find(), count(), equal_range()
 * 
 * Buckets:
 * * bucket_count(), max_bucket_count(), bucket_size(), 
 * * bucket(): locate element's bucket
 * 
 * Hash policy:
 * load_factor(): get load factor (ratio between the number of elements in the container (`size`) and the number of buckets (`bucket_count`))
 * max_load_factor()
 * rehash(): set number of buckets
 * reserve(): request a capacity change
 **/

#include <iostream>
#include <unordered_set>
#include <string>


class Book
{
public:
	Book(int32_t year, const std::string& title)
		: year{year}, title{title} {}

	// overloading for user-defined type in std::unordered_set
	inline bool operator== (const Book& other) const { return year == other.year; }

	friend std::ostream& operator<< (std::ostream& stream, const Book& book)
	{
		stream << book.year << ": " << book.title;
		return stream;
	}

public:
	int32_t year;
	std::string title;
};

// custom hash function template for user-defined types
class BookHashFunc
{
public:
	inline size_t operator()(const Book& book) const { return book.year; }
};


int main()
{
	std::unordered_set<int32_t> uset = { 4, 1, 3, 8, 3, 2, 5, 6, 4 };
	uset.emplace(45);
	uset.emplace_hint(uset.begin(), 55);

	std::cout << "Hash set info:\n"
			  << "size = "            << uset.size()            << '\n'
			  << "max_size = "        << uset.max_size()        << '\n'
			  << "bucket_count = "    << uset.bucket_count()    << '\n'
			  << "load_factor = "     << uset.load_factor()     << '\n'
			  << "max_load_factor = " << uset.max_load_factor() << '\n';

	std::cout << "\n----------\nElements of uset:\n";
	for (auto& u : uset)
		std::cout << u << '\n';


	std::cout << "\n----------\nstd::unordered_set for user-defined type:\n";
	std::unordered_set<Book, BookHashFunc> bookList = {
		{ 1998, "A Clash of Kings" }, 
		{ 2011, "A Dance with Dragons" }, 
		{ 1996, "A Game of Thrones" }, 
		{ 2005, "A Feast for Crows" }, 
		{ 2000, "A Storm of Swords" }, 
		{ 2005, "The Book Thief" } // this will be omitted
	};

	for (auto& book : bookList)
		std::cout << book << '\n';
}