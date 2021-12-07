#pragma once
#include <iostream>

template<typename T>
class Node
{
public:
	Node() : value(), next(nullptr) {}
	Node(T val, Node* next = nullptr) : value(val), next(next) {}

public:
	T value;
	Node* prev;
	Node* next;
};

template<typename T>
void Print(Node<T>* head)
{
	for (Node<T>* itr = head; itr != nullptr; itr = itr->next)
	{
		std::cout << "[value = " << itr->value << ", next = " << itr->next << "]\n";
	}
}

template<typename T>
T Search(Node<T>* head, T key)
{
	for (Node<T>* itr = head; itr != nullptr; itr = itr->next)
	{
		if (itr->value == key)
			return itr->value;
	}
	return T();
}

