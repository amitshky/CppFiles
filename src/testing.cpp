#include <iostream>

template<typename T>
class DArray final {
public:
	DArray() 
		: _size{0},
		  _capacity{2},
		_data{ static_cast<T*>(operator new[](_capacity * sizeof(T))) } { }

	~DArray() {
		Clear();
	}

	void PushBack(const T& val) {
		ReAlloc();
		_data[_size++] = val;
	}

	void PushBack(T&& val) {
		ReAlloc();
		_data[_size++] = val;
	}

	template<typename... Args>
	void EmplaceBack(Args&&... args) {
		ReAlloc();
		new(&_data[_size++]) T{ std::forward<T>(args...) }; // placement new
	}

	[[nodiscard]] inline size_t Size() const { return _size; }
	[[nodiscard]] inline size_t Capacity() const { return _capacity;  }

	[[nodiscard]] inline T& operator[](size_t i) { return _data[i]; }

private:
	void ReAlloc() {
		if (_size >= _capacity)
			return;

		_capacity += 4;
		T* temp = static_cast<T*>(operator new[](_capacity * sizeof(T)));
		for (size_t i = 0; i < _size; ++i) {
			new(&temp[i]) T{ std::move(_data[i]) };
		}

		for (size_t i = 0; i < _size; ++i) {
			_data[i].~T();
		}
		operator delete[](_data, _capacity * sizeof(T);
		_data = temp;
	}

	void Clear() {
		for (size_t i = 0; i < _size; ++i) {
			_data[i].~T();
		}

		_size = 0;
		_capacity = 0;

		operator delete[](_data, _capacity * sizeof(T);
		_data = nullptr;
	}

private:
	size_t _size;
	size_t _capacity;
	T* _data;
};

int main() {
	struct S {
		int a = 5;

		S(int val) : a(val) {}
	};

	DArray<S> a;

	a.EmplaceBack(5);
	a.EmplaceBack(4);
	a.EmplaceBack(3);
	a.EmplaceBack(2);
	a.EmplaceBack(1);

	for (size_t i = 0; i < a.Size(); ++i) {
		std::cout << a[i].a << '\n';
	}

	std::cin.get();
}