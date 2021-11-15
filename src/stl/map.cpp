/**
 * std::map<KeyType, ValueType, Compare>
 * 
 * 1. Associative container that stores elements in key-value combination
 * 2. Keys are unique, but values can be same
 * 3. Implemented using self-balancing biniary tree
 * 4. Stores key-value in sorted ordered (based on the key)
 * 5. For user-defined datatype, you need to overload comparision operators
 * 
 * Iterators:
 * * begin(), cbegin(), end(), cend(), rbegin(), crbegin(), rend(), crend()
 * 
 * Capacity:
 * * empty(), size(), max_size()
 * 
 * Element access:
 * [], at() // C++11
 * 
 * Modifiers:
 * * clear(), insert(), emplace(), erase(), swap()
 * * emplace_hint(): constructs elements in-place with hint
 * 
 * Operations:
 * * find(), count(), equal_range()
 * 
 * 
 * Multimap: you can have duplicate keys
 * use equal_range() function to get all values of given key
 **/

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional> // for std::greater, std::less


class Account
{
public:
	Account(const std::string& username)
		: username(username), userID(Account::s_UserID++) {}

	inline bool operator< (const Account& other) const { return username < other.username; }
	inline bool operator> (const Account& other) const { return username > other.username; }

	friend std::ostream& operator<< (std::ostream& stream, const Account& account)
	{
		stream << '[' << account.userID << "]: " << account.username;
		return stream;
	}

public:
	static uint32_t s_UserID;
	std::string username;
	uint32_t userID;
};

uint32_t Account::s_UserID = 0;


int main()
{
	std::map<std::string, int32_t, std::greater<std::string>> phoneBook;
	phoneBook["Name1"] = 1234;
	phoneBook["Name2"] = 2345;
	phoneBook["Name2"] = 3456; // will be omitted
	phoneBook["Name3"] = 3456;

	for (auto& [key, value] : phoneBook) // C++17
		std::cout << key << ": " << value << '\n';

	//for (auto& p : phoneBook)
	//	std::cout << p.first << ": " << p.second << '\n';

	// std::map for user defined datatype
	std::cout << "\n------\nstd::map for user-defined datatype:\n";

	std::map<Account, std::vector<std::string>> database;
	database[Account("username14")].push_back("first post of username14");
	database[Account("username14")].push_back("second post of username14");

	// the output will be sorted according to the username
	Account user3("username3");
	database.emplace(user3, std::vector<std::string>{ "first post of username3" });

	for (auto& [key, value] : database) // C++17
	{
		std::cout << key << ":\nPost:\n";
		for (auto& v : value)
			std::cout << v << '\n';
	}

	// Multimap
	std::cout << "\n-------\nstd::multimap:\n";

	std::multimap<char, int32_t> multimap;
	multimap.insert(std::make_pair('a', 1));
	multimap.insert(std::make_pair('a', 2));
	multimap.insert(std::make_pair('b', 1));
	multimap.insert(std::make_pair('b', 2));

	for (auto& [key, value] : multimap)
		std::cout << key << ": " << value << '\n';

	// to access all elements having the same key
	auto range = multimap.equal_range('a'); // returns std::pair<iterator, iterator> and takes key as parameter
	for (auto it = range.first; it != range.second; it++) // range.first is an iterator for first key-value pair of the given key (in this case 'a') 
	                                                      // and range.second is the iterator for the last key-value pair of the given key (in this case 'a') 
	{
		//           key                 value              // because key and value are stored as std::pair
		std::cout << it->first << ' ' << it->second << '\n';
	}

	auto itr = multimap.find('a');
	if (itr != multimap.end())
		std::cout << itr->first << ' ' << itr->second << '\n';
}