/**
 * Variadic Templates
 * - write functions that take arbitrary number of arguments in a type-safe way
 * - typename... args => template parameter pack
 * - Args... args => function parameter pack
 * - variadic templates are written the same way as recursive code
 * 
 * Catch all functions
 * - does not use traditional recursive approach of implementing variadic templates
 * - any template parameter can go anywhere
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

// Basic
template<typename T>
T Adder(T v)
{
	//std::cout << __FUNCSIG__ << "\n";
	return v;
}

template<typename T, typename... Args>
T Adder(T first, Args... args)
{
	//std::cout << __FUNCSIG__ << "\n";
	return first + Adder(args...);
}

template<typename T>
std::string ToString(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

template<typename T, typename... Args>
std::string ToString(T t, const Args&... args)
{
	std::stringstream ss;
	ss << t;
	ss << ToString(args...);
	return ss.str();
}

template<typename... Args>
std::vector<std::string> ToStringVec(const Args&... args)
{
	return { ToString(args)... }; // calling initializer list of vector
}

// Variadic tuple
template<typename... Ts>
class Tuple {}; // empty base case // consumes no space // empty base optimization

template<typename T, typename... Ts>
class Tuple<T, Ts...> : public Tuple<Ts...>
{
public:
	Tuple(T t, Ts... ts) :Tuple<Ts...>(ts...), tail(t) {}

	T tail;
};

// to access elements of the tuple // helper class that holds the type of the k-th element in a tuple
template<size_t, typename> 
class ElemTypeHolder;

template<typename T, typename... Ts>
class ElemTypeHolder<0, Tuple<T, Ts...>>
{
public:
	typedef T type;
};

template<size_t k, typename T, typename... Ts>
class ElemTypeHolder<k, Tuple<T, Ts...>>
{
public:
	typedef typename ElemTypeHolder<k - 1, Tuple<Ts...>>::type type;
};

template<size_t k, typename... Ts>
typename std::enable_if<k == 0, typename ElemTypeHolder<0, Tuple<Ts...>>::type&>::type get(Tuple<Ts...>& t)
{
	return t.tail;
}

template<size_t k, typename T, typename... Ts>
// std::enable_if is used to select between two template overloads of get
// one is for when k = 0 and other for general case
typename std::enable_if<k != 0, typename ElemTypeHolder<k, Tuple<T, Ts...>>::type&>::type get(Tuple<T, Ts...>& t)
{
	Tuple<Ts...>& base = t;
	return get<k - 1>(base);
}

// Catch all functions
/**
 * print fucntion for standard library containers
 * many STL containers are templates that can be parameterized by value type and allocator type
 * but this function won't work for std::map, std::set because it uses 4 template arguments not 2
 * so we use variadic templates
 */

//template<template<typename, typename> class ContainerType, typename ValueType, typename AllocType>
//void PrintContainer(const ContainerType<ValueType, AllocType>& c)
//{
//	for (const auto& val : c)
//		std::cout << val << ' ';
//	std::cout << "\n";
//}

template<template<typename, typename...> class ContainerType, typename ValueType, typename... Args>
void PrintContainer(const ContainerType<ValueType, Args...>& c)
{
	for (const auto& val : c)
		std::cout << val << ' ';
	std::cout << "\n";
}

// overload << for std::pair // iteration goes over key and value
template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& p)
{
	out << "[" << p.first << ", " << p.second << "]";
	return out;
}

// Forwarding
//template<typename T, typename... Args>
//std::unique_ptr<T> make_unique(Args&&... args)
//{
//	return std::unique_ptr(new T(std::forward<Args>(args)...));
//}

int main()
{
	//// Basic
	//int64_t sum = Adder(1, 2, 3, 4, 5);
	//std::string x = "x", y = "y", z = "z";
	//std::string strSum = Adder(x, y, z);
	//std::cout << sum << "\n" << strSum << std::endl;

	//std::cout << ToString("hello", 1, 2, 3, 4, 5, 6, 7, 8, 9) << std::endl;
	//std::vector<std::string> vec = ToStringVec("hello", 1, 2, 3, 4, 5, 6, 7, 8, 9);
	//for (auto& v : vec)
	//	std::cout << v << std::endl;

	//// Variadic tuple
	//Tuple<int, float, const char*> t1(1, 2.3f, "Hello");
	//std::cout << "0th elem is " << get<0>(t1) << "\n";
	//std::cout << "1st elem is " << get<1>(t1) << "\n";
	//std::cout << "2nd elem is " << get<2>(t1) << "\n";

	//get<0>(t1) = 23;
	//std::cout << "0th elem is " << get<0>(t1) << "\n";

	//// Catch all functions
	//std::vector<double> vd{ 3.14, 8.1, 3.2, 1.0 };
	//PrintContainer(vd);

	//std::map<std::string, int> mapObj{ {"foo", 42}, {"bar", 81}, {"bazzo", 4} };
	//PrintContainer(mapObj);

	// Forwarding
	std::unique_ptr<int> ptr = std::make_unique<int>(1, 2);


	std::cin.get();
	return 0;
}
