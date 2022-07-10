#pragma once

#include <array>

template<int N>
void LCGRand(std::array<float, N>& randNums, int seed, int a, int c, int m)
{
	for (auto& randNum : randNums)
	{
		seed = (a * seed + c) % m;
		randNum = float(seed);
		//randNum = float(seed) / float(m);
	}
}
