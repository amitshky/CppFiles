#pragma once
#include <type_traits>

template<typename... Ts>
class Tuple {};

template<typename T, typename... Ts>
class Tuple<T, Ts...> : public Tuple<Ts...>
{
public:
	Tuple(T t, Ts... ts) : Tuple<Ts...>(ts...), tail(t) {}

	T tail;
};

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
typename std::enable_if<k == 0, typename ElemTypeHolder<0, Tuple<Ts...>>::type&>::type Get(Tuple<Ts...>& t)
{
	return t.tail;
}

template<size_t k, typename T, typename... Ts>
typename std::enable_if<k != 0, typename ElemTypeHolder<k, Tuple<T, Ts...>>::type&>::type Get(Tuple<T, Ts...>& t)
{
	Tuple<Ts...>& base = t;
	return Get<k - 1>(base);
}
