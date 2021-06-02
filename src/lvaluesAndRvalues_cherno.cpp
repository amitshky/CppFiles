#include <iostream>

int GetValue()
{
	return 5;
}

void PrintName(const std::string& name)
{
	std::cout << "lvalue: " << name << std::endl;
}

void PrintName(std::string&& name)
{
	std::cout << "rvalue: " << name << std::endl;
}

int main()
{
	// lvalue	rvalue
	//int i	=	10;
	// lvalue = has location
	// rvalue = cannot assign value to it
	// rvalue = temporary value
	// 10 = i // not possible
	
	// cannot take an lvalue reference from an rvalue for non-const
	//int& a = 10; //error
	const int& a = 10; // no error
	
	int i = GetValue();
	// GetValue() returns an rvalue

	std::string firstName = "Amit";
	std::string lastName = "Shakya";
	// lvalue			// rvalue
	std::string Name = firstName + lastName;
	PrintName(firstName); // no error
	//PrintName(firstName + lastName); // error // give && to function arg or give const
	std::string&& rvalueRef = firstName + lastName; // rvalue refernce
	PrintName(firstName + lastName);


	std::cin.get();
	return 0;
}