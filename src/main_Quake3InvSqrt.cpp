#include <iostream>
#include <cmath>
#include <bitset>

float QInvSqrt(float number)
{
	int32_t i;
	float x2, y;

	x2 = number * 0.5f;
	y  = number;

	i  = *(int32_t*)&y;         // bit hack to manipulate the original floating point number
	i  = 0x5f3759df - (i >> 1); // what the fuck
	y  = *(float*)&i;
	y *= (1.5f - x2 * y * y);   // 1st iteration
//	y *= (1.5f - x2 * y * y);   // 2nd iteration not required

	return y;
}

int main()
{
	//float val = 0.2f;
	//int32_t valInt = *(int32_t*)&val; // cool bit hack // since we cannot manipulate bits of a float
	//std::cout << std::bitset<32>(valInt) << '\n' 
	//		  << std::bitset<32>(0x5f3759df) << '\n';

	float num = 256;
	std::cout << "QSqrt = " << QInvSqrt(num) << '\n'
			  << "Sqrt  = " << 1.0f / std::sqrt(num) << '\n';
}