#include <iostream>
#include <memory>
#include <string>

struct AllocationMetrics
{
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed     = 0;

	uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t bytes)
{
	s_AllocationMetrics.TotalAllocated += bytes;
	return malloc(bytes);
}

void operator delete(void* mem, size_t bytes)
{
	s_AllocationMetrics.TotalFreed += bytes;
	free(mem);
}

static void PrintMemoryUsage()
{
	std::cout << "Memory Usage = " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}

class Empty
{
public:
	Empty(int value) : i(value) {}

	int i;
};

int main()
{
	PrintMemoryUsage();
	{
	std::string str = "Hello World, wht up?";
	{
		PrintMemoryUsage();
		std::unique_ptr<Empty> i = std::make_unique<Empty>(5);
		PrintMemoryUsage();
	}
	PrintMemoryUsage();
	}
	PrintMemoryUsage();

	std::cin.get();
	return 0;
}
