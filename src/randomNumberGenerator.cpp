#include <iostream>

uint32_t BaseHash(uint32_t x, uint32_t y)
{
	x = 1103515245U * ((x >> 1U) ^ x);
	y = 1103515245U * ((y >> 1U) ^ y);
	
	uint32_t h32 = 1103515245U * (x ^ (y >> 3U));
	return h32 ^ (h32 >> 16);
}

float hash12(float x, float y)
{
	// can be used to get bits of the floating point number
	union FloatToBits
	{
		float f;
		uint32_t u;
		
		FloatToBits(float f)
		  : f{f} {}
	};
	
	FloatToBits xF{x};
	FloatToBits yF{y};
	
	uint32_t n = BaseHash(xF.u, yF.u);
	return static_cast<float>(n) * (1.0 / static_cast<float>(0xffffffffU));
}

int main()
{
	std::cout << hash12(-1.0f, 1.0f) << '\n';
}