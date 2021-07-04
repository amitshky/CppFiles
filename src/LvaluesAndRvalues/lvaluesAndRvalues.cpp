/**
 * https://www.internalpointers.com/post/understanding-meaning-lvalues-and-rvalues-c
 */

#include <iostream>
#include <string>

#define BASICS                 0
#define LVALUE_TO_RVALUE_CONV  0
#define LVALUE_REF             0
#define CONST_LVALUE_REF       0
#define RVALUE_REF             1


#if BASICS
static int32_t global = 10;

int32_t getGlobal() // returns the value of `global` // rvalue
{
	return global;
}

int32_t& getGlobalRef() // returns the variable `global` // lvalue
{
	return global;
}
#endif

#if LVALUE_REF
void func(int32_t& val)
{
	val++;
}
#endif

#if CONST_LVALUE_REF
void funcConst(const int32_t& val)
{
	std::cout << val << '\n';
}
#endif

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
	// -------- Basics ------------------------------------
#if BASICS
	// lvalues: think of them as containers 
	// 			they represent a certain memory location
	// rvalues: think of them as things in a container
	// 			they don't specifically have a memory location
	// 			they are short-lived or temporary

	//      lvalue     rvalue
	int32_t   var   =    5;
	// thus assignment requires an lvalue as its left operand 
	//int y;
	//5 = y; // error // must be a modifiable lvalue

	int32_t* y = &var; // `&` operator takes in an lvalue and gives an rvalue

	//getGlobal() = 5;    // error // returns an rvalue ie the value of global
	getGlobalRef() = 5; // no error // returns the global // thus an lvalue
#endif

	// -------- lvalue to rvalue conversion ---------------
#if LVALUE_TO_RVALUE_CONV
	// lvalues can be converted to rvalues
	int a = 8, b = 9;
	int32_t result = a + b;
	// here the `+` operator takes in 2 rvalues and returns an rvalue
	// `a` and `b` are lvalues which get implicitly converted into rvalues
#endif
	// -------- lvalue reference --------------------------
#if LVALUE_REF
	int32_t lval = 2;
	int32_t& lvalRef = lval; // lvalue reference can only be assigned to a modifyable lvalue (non-const)
	lvalRef++; // you can modify `lval` using `lvalRef`

	//int32_t& lvalRef2 = 10; // error // cannot assign rvalue to a non-const lvalue ref
	// this means that you cannot convert an rvalue to an lvalue
	// think about this, will you be able to modify a numeric constant (rvalue) i.e., 10 through lvalue reference?
	// what happens to the lvalue reference when the numeric constant is gone

	//func(10); // error
	func(lval); // no error
	std::cout << lval << '\n';
#endif

	// -------- const lvalue reference --------------------
#if CONST_LVALUE_REF
	// this is an exception to the earlier rule of not being allowed to bind an rvalue to an lvalue reference
	// we can bind it if we have a const lvalue reference
	// const lvalue ref can take both lvalues and rvalues
	funcConst(10); // this works
	// this is because a numeric constant like 10 is volatile
	// so if we make the reference itself constant, the value its pointing to cannot be modified
#endif

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