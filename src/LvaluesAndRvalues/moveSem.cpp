/**
 * https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners
 * https://www.learncpp.com/cpp-tutorial/rvalue-references/
 */

#include <iostream>
#include <string>

#define RVALUE_REF 0

#if RVALUE_REF
int32_t g_X = 5;
int32_t& GetNum() // returns an lvalue
{
	return g_X;
}

//                const lvalue reference           rvalue reference
std::string Join(const std::string& constLvalRef, std::string&& rvalRef) // returns an rvalue
{
	return constLvalRef + rvalRef;
}
#endif


int main()
{
#if RVALUE_REF

	// rvalue reference lets you modify temporary values (rvalues)
	// available from C++11
	// unlike const lvalue ref, rvalue ref lets you modify the rvalue
	// rvalue ref can only be initialized with rvalues

	int32_t x = 10;
	int32_t y = 2;
	int32_t&& rvalRef = x + y + GetNum(); // rvalue reference
	rvalRef++; // modifying the rvalue
	std::cout << rvalRef << '\n';

	std::string hello = "Hello ";
	std::string world = "world!";
	std::string&& helloWorldRRef = hello + world; // hellow + world results in an rvalue
	helloWorldRRef += ", sup?"; // modifying the rvalue
	std::cout << helloWorldRRef << '\n';

#endif

}