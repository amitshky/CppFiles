#include <iostream>

class String
{
public:
	String() = default;
	String(const char* string)
	{
		printf("Created!\n");
		m_Size = strlen(string);
		m_Data = new char[m_Size];
		memcpy(m_Data, string, m_Size);
	}
	String(const String& other) // copy constructor
	{
		printf("Copied!\n");
		m_Size = other.m_Size;
		m_Data = new char[m_Size];
		memcpy(m_Data, other.m_Data, m_Size);
	}
	String(String&& other) noexcept // move constructor
	{
		printf("Moved!\n");
		m_Size = other.m_Size;
		m_Data = other.m_Data; // this does not copy // only transfers the pointer

		other.m_Size = 0;
		other.m_Data = nullptr;
	}

	String& operator=(String&& other) noexcept // assignment operator overload
		// we are not constructing a new object 
		// but we are moving another object into this object
		// the object might have mem allocation so potential for memory leak
		// also check if the contents of these objects are same (like assigning to itself)
	{
		printf("Moved!\n");
		if (this != &other)
		{
			delete[]m_Data; // to override this object with another object

			m_Size = other.m_Size;
			m_Data = other.m_Data; // this does not copy // only transfers the pointer

			other.m_Size = 0;
			other.m_Data = nullptr;
		}
		return *this;
	}

	~String()
	{
		printf("Destroyed!\n");
		delete[]m_Data;
	}

	void Print()
	{
		for (int i = 0; i < m_Size; i++)
			printf("%c", m_Data[i]);
		printf("\n");
	}

private:
	char* m_Data;
	uint32_t m_Size;
};

class Entity
{
public:
	Entity(const String& name)
		:m_Name(name) {}
	Entity(String&& name)
		:m_Name(std::move(name)) {} // (String&&)name // casting 

	void PrintName() { m_Name.Print(); }

private:
	String m_Name;
};

int main()
{
	//Entity ett("Amit");
	//ett.PrintName();

	String hello = "Hello";
	//String dest = std::move(hello); // calling the move constructor // not a move assignment // creating a new variable
	String dest;

	std::cout << "Hello: ";
	hello.Print();
	std::cout << "dest: ";
	dest.Print();
	dest = std::move(hello); // move assignment // on an existing variable
	std::cout << "Hello: ";
	hello.Print();
	std::cout << "dest: ";
	dest.Print();

	std::cin.get();
	return 0;
}
