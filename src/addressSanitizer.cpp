/**
 * References:
 * https://embeddedbits.org/finding-memory-bugs-with-addresssanitizer/
 * https://docs.microsoft.com/en-us/cpp/sanitizers/asan-error-examples?view=msvc-170
 * 
 * Address Sanitizer
 * Address Sanitizer detects memory corruption bugs such as buffer overflows or accesses to a dangling pointer
 * 
 * Detects:
 * - Buffer overflow
 * - Stack overflow
 * - Heap overflow
 * - Memory leak
 * - Dangling pointers // use after free
 * - Uninitialized variables
 * 
 * How it works:
 * For memory leaks: malloc and free are replaced so that the memory is allocated and deallocated by ASAN
 * Buffer overflows: all memory tht shouldnt be accessed is poisoned
 * 	- the address space of the application is divided into main application memory (used by application)
 * 	- and shadow memory (stores metadata about poisoned memory)
 * 	- maps every 8 bytes of application memory into 1 byte of shadow memory
 * 		- for poisoned memory, an associated bit of shadow memory is set to 1 
 * 		- for unpoisoned memory, an associated bit of shadow memory is set to 0 
 * 
 * Other tools:
 * - Thread sanitizer // concurrency problems
 * - Memory sanitizer
 * - Hardware-assisted address sanitizer
 * - Undefined behavior sanitizer
 * - Kernel address sanitizer // dynamic memory error detector for linux kernel
 */

#include <iostream>
#include <cstring> // memcpy
#include <memory>

#define ALLOCATION_SIZE_TOO_BIG  0
#define CALLOC_OVERFLOW          0
#define NEW_DELETE_TYPE_MISMATCH 0

#if NEW_DELETE_TYPE_MISMATCH
class Base
{
public:
	Base() {}
	~Base() { std::cout << "Base Destructor\n"; } // should be virtual
};

class Derived : public Base
{
public:
	int var;
	Derived() : var(100) {}
	~Derived() { std::cout << "Derived Destructor\n"; }
};
#endif

int main()
{
#if ALLOCATION_SIZE_TOO_BIG
	int x = 1000;
	int y = 1000;
	char* buffer = (char*)malloc(x * y * x * y); // error
	memcpy(buffer, buffer + 8, 8);
#endif 

#if CALLOC_OVERFLOW
	int number = -1; // number of each elements
	int size = 1000; // length in bytes of each element
	void* ptr = calloc(number, size); // error
	std::cout << ptr << '\n';
#endif

#if NEW_DELETE_TYPE_MISMATCH
	Base* b = new Derived();
	delete b;
#endif
}