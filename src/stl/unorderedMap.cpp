/**
 * std::unordered_map<KeyType, ValueType, Hash>
 * 
 * 1. Associative container that contains key-value pairs with unique keys
 * 2. Search, insertion, and removal have constant time complexity
 * 3. Uses hashing to insert elements into the buckets, elements are organized into buckets
 * 4. Fast element access
 * 5. The elements are not sorted
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
#include <unordered_map>
#include <string>


class Account
{
public:
	Account(const std::string& username)
		: username(username), userID(Account::s_UserID++) {}

	// overloading for custom hash function
	inline bool operator== (const Account& other) const { return userID == other.userID; }

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

// custom hash function template for user-defined types
class AccountHashFunc
{
public:
	inline size_t operator() (const Account& account) const { return account.userID; }
};


int main()
{
	// initializing
	std::unordered_map<std::string, int32_t> umap = {
		{ "user1", 1 },
		{ "user3", 3 },
		{ "user3", 6 },
		{ "user2", 2 }
	}; 
	// we can also insert like this
	umap["user5"] = 5;
	// update
	umap["user3"] = 4;

	std::cout << "Hash map info:\n"
			  << "size = "            << umap.size()            << '\n'
			  << "max_size = "        << umap.max_size()        << '\n'
			  << "bucket_count = "    << umap.bucket_count()    << '\n'
			  << "load_factor = "     << umap.load_factor()     << '\n'
			  << "max_load_factor = " << umap.max_load_factor() << '\n';
	
	// element lookup
	if (umap.find("user1") != umap.end())
		std::cout << "umap[\"user1\"] = " << umap["user1"] << '\n';

	std::cout << "umap.count(\"user3\") = " << umap.count("user3") << '\n';

	// output is not sorted
	std::cout << "elements in umap:\n";
	for (auto& [key, value] : umap) // C++17
		std::cout << key << ": " << value << '\n';

	
	std::cout << "\n----------\nstd::unordered_map for user-defined type:\n";
	std::unordered_map<Account, int32_t, AccountHashFunc> accountList = {
		{ Account("user1"), 1 },
		{ Account("user2"), 2 },
		{ Account("user3"), 3 }
	};

	std::cout << "elements in accountList:\n";
	for (auto& [key, value] : accountList) // C++17
		std::cout << key << ": " << value << '\n';
}