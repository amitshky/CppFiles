#include <iostream>
#include <memory>
#include <vector>

// to run specific sections of the code 
#define PTR_BASICS       0
#define STACK_HEAP       1
#define POLYMORPHS       0
#define VECTOR_PTR       0
#define PTR_PASSING      0
#define CUS_SMART_PTR    0 // custom smart pointer


static size_t totalAlloc = 0;
static size_t totalFreed = 0;

void* operator new(size_t sz)
{
	//puts("@@@@ allocated mem @@@@");
	if (sz == 0)
		sz++; // avoid std::malloc(0) which may return nullptr on success

	totalAlloc += sz;

	if (void* ptr = std::malloc(sz))
		return ptr;
	
	throw std::bad_alloc{}; // required by [new.delete.single]/3
}

void operator delete(void* mem, size_t sz)
{
	//puts("#### deallocated mem ####");
	totalFreed += sz;
	std::free(mem);
	//::operator delete(mem);
}

void operator delete[](void* mem, size_t sz)
{
	//puts("#### deallocated mem ####");
	totalFreed += sz;
	std::free(mem);
	//::operator delete(mem);
}

void MemUsage()
{
	std::cout << "Total Allocated   = " << totalAlloc << '\n'
			  << "Total Deallocated = " << totalFreed << '\n';
}


#if POLYMORPHS
class Base
{
public:
	Base()
	{
		std::cout << "----Base Constructor----\n";
	}

	virtual ~Base()
	{
		std::cout << "----Base Destructor----\n";
	}

	virtual void Print()
	{
		std::cout << "from Base\n";
	}

private:
	uint64_t m_HexBase = 0xa1a2a3a4a5a6a7a8;
};

class DerivedA : public Base
{
public:
	DerivedA()
	{
		std::cout << "----Derived-A Constructor----\n";
	}

	~DerivedA()
	{
		std::cout << "----Derived-A Destructor----\n";
	}

	void Print() override 
	{
		std::cout << "from Derived-A\n";
	}

private:
	uint64_t m_HexDerA = 0xb1b2b3b4b5b6b7b8;
};

class DerivedB : public Base
{
public:
	DerivedB()
	{
		std::cout << "----Derived-B Constructor----\n";
	}

	~DerivedB()
	{
		std::cout << "----Derived-B Destructor----\n";
	}

	void Print() override 
	{
		std::cout << "from Derived-B\n";
	}

private:
	uint64_t m_HexDerB = 0xc1c2c3c4c5c6c7c8;
};

#endif

#if VECTOR_PTR
struct Entity
{
	Entity()
	{
		std::cout << "----NTT Created----\n";
	}

	~Entity()
	{
		std::cout << "----NTT Destroyed----\n";
	}

	const char* Name = "NTT";
	const int32_t id = 12345;
};
#endif

#if PTR_PASSING
static int32_t id = 0;

class Data
{
public:
	Data(uint32_t data)
		: m_Data(data)
	{
		std::cout << "Data " << m_Data << " created\n";
	}

	void PrintData(const char* loc)
	{
		std::cout << loc << ' ' << m_Data << '\n';
	}

	~Data()
	{
		std::cout << "Data " << m_Data << " destroyed\n";
	}

private:
	uint32_t m_Data;
};

void AccessPtr(Data* data)
{
	data->PrintData("Inside");
	data = new Data(id++);
	data->PrintData("Inside");
	delete data;
}

void AccessShPtr(std::shared_ptr<Data> data) // shares the ownership of the memory
{
	data->PrintData("Inside");
	std::cout << "Reference count = " << data.use_count() << '\n'; // 2
	data = std::make_shared<Data>(id++);
	std::cout << "Reference count = " << data.use_count() << '\n'; // 1
	data->PrintData("Inside");
}

void AccessShPtrRef(std::shared_ptr<Data>& data) // doesn't share the ownership of the memory 
	// the pointer can be changed 
	// `const std::shared_ptr<Type>& arg` if you dont want to share ownership
{
	data->PrintData("Inside");
	std::cout << "Reference count = " << data.use_count() << '\n';
	data = std::make_shared<Data>(id++); // pointer changed
	std::cout << "Reference count = " << data.use_count() << '\n';
	data->PrintData("Inside");
}

void DoublePtr(Data** data) // if you want to modify the actual pointer
	// this comes from C // C had no concept of references
	// Data** data = NULL is possible, so a reference might be safer
{
	(*data) = new Data(id++); // a useless example
}

void RefPtr(Data*& data) // here `data` cannot be NULL
{
	data = new Data(id++);
}
#endif

#if CUS_SMART_PTR

template<typename T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = nullptr) : m_Ptr(ptr) {}
	~AutoPtr() { delete m_Ptr; }

	inline T* operator-> () const { return  m_Ptr; }
	inline T& operator*  () const { return *m_Ptr; }

private:
	T* m_Ptr;
};

class SomeClass
{
public:
	SomeClass()  { std::cout << "SomeClass created\n";   }
	~SomeClass() { std::cout << "SomeClass destroyed\n"; }

	inline uint64_t GetMax() const { return m_Max; } 

private:
	uint64_t m_Max = ~0ULL;
};

#endif


int main()
{
	// ----------Pointer basics----------------------------
#if PTR_BASICS
	int32_t a   = 5;
	int32_t* b  = &a; // b stores address of a
	int32_t** c = &b; // c stores address of b

	std::cout << "a   = " << a   << '\n' // display value a
			  << "b   = " << b   << '\n' // display address of a
			  << "*b  = " << *b  << '\n' // display value in address of a // value of a
			  << "c   = " << c   << '\n' // display address of b
			  << "*c  = " << *c  << '\n' // display value in address of b // address of a
			  << "**c = " << **c << '\n' // display value in address pointed by the address in b // value of a
			  << "sizeof(a) = "  << sizeof(a) << "bytes\n"
			  << "sizeof(b) = "  << sizeof(b) << "bytes\n"
			  << "sizeof(c) = "  << sizeof(c) << "bytes\n";

	b = b + 1; // increments by the sizeof the datatype b is pointing to
	std::cout << "b + 1 = " << b << '\n';
#endif

	// ----------Stack and Heap allocations----------------
#if STACK_HEAP
	constexpr int32_t arrSize = 10;
	constexpr size_t  bytes   = arrSize * sizeof(int32_t);

	// stack allocation (compile time)
	int stackArr[arrSize] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// heap allocation (runtime)
	//int32_t* arr = (int32_t*)malloc(bytes); // c style
	//free(arr);
	
	int32_t* heapArr = new int32_t[arrSize];
	delete[] heapArr;

	int32_t** ptr = new int32_t*[arrSize];
	for (int i = 0; i < arrSize; i++)
		ptr[i] = new int32_t;
	for (int i = 0; i < arrSize; i++)
		delete ptr[i];
	delete[] ptr;
#endif

	// ----------Polymorphism------------------------------
#if POLYMORPHS

	Base* base = new DerivedA();
	base->Print();
	delete base; // else memory allocated for DerivedA won't be freed
	base = new DerivedB();
	base->Print();
	delete base;
	
#endif

#if VECTOR_PTR
	
	{
		std::vector<Entity*> vecEntity;
		vecEntity.push_back(new Entity());
		vecEntity.push_back(new Entity());
		vecEntity.push_back(new Entity());
		vecEntity.push_back(new Entity());

		for (auto& v : vecEntity) // has to be reference // auto& v
			delete v;

		vecEntity.clear();
	}
	
#endif

#if PTR_PASSING 
	Data* data;
	DoublePtr(&data);
	AccessPtr(data);
	data->PrintData("Outside");
	delete data;

	{
		//std::shared_ptr<Data> shData = std::make_shared<Data>(id++);
		//AccessShPtr(shData);
		//shData->PrintData("Outside");
	}
#endif

#if CUS_SMART_PTR

	{
		AutoPtr<SomeClass> ptr(new SomeClass());
		std::cout << std::hex << ptr->GetMax() << '\n';
	}

#endif

	MemUsage();
}