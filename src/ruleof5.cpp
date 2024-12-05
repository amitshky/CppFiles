#include <iostream>

class Buffer {
public:
	// constructor
	explicit Buffer(size_t bytes = 1)
		: _data{ nullptr },
		_size{ bytes } {
		_data = new int[bytes];
		for (size_t i = 0; i < bytes; ++i) {
			_data[i] = i;
		}
	}

	// destructor
	~Buffer() {
		delete[] _data;
		_data = nullptr;

		std::cout << "Resources deleted!\n";
	}

	// copy constructor
	Buffer(const Buffer& other)
		: _data{ nullptr },
		_size{ other._size } {
		if (this == &other)
			return;

		delete[] _data;

		_data = new int[other._size];
		_size = other._size;
		for (size_t i = 0; i < other._size; ++i) {
			_data[i] = other._data[i];
		}

		std::cout << "Resources copied!\n";
	}

	// copy assigment operator
	Buffer& operator=(const Buffer& other) {
		if (this == &other)
			return *this;

		delete[] _data;

		_data = new int[other._size];
		_size = other._size;
		for (size_t i = 0; i < other._size; ++i) {
			_data[i] = other._data[i];
		}

		std::cout << "Resources copied!\n";
		return *this;
	}

	// move constructor
	Buffer(Buffer&& other) noexcept
		: _data{ nullptr }, _size{ 0 } {
		if (this == &other)
			return;

		delete[] _data;

		_data = other._data;
		_size = other._size;

		other._data = nullptr;
		other._size = 0;

		std::cout << "Resources moved!\n";
	}

	// move assignment operator
	Buffer& operator=(Buffer&& other) noexcept {
		// you can implement as in copy constructor or use std::move
		delete[] _data;
		*this = std::move(other);

		std::cout << "Resources moved!\n";
	}

	friend std::ostream& operator<<(std::ostream& stream, const Buffer& buffer);

private:
	int* _data;
	size_t _size;
};

std::ostream& operator<<(std::ostream& stream, const Buffer& buffer) {
	for (int i = 0; i < buffer._size; ++i) {
		stream << buffer._data[i] << '\n';
	}

	return stream;
}

int main() {
	{
		Buffer buff{ 5 };
		Buffer b{ buff };
		Buffer b2{ std::move(buff) };
		std::cout << b;
	}
	std::cin.get();
}