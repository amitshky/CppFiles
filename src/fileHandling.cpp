/**
 * References:
 * https://courses.cs.vt.edu/cs2604/fall03/binio.html
 * https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-2.html
 * 
 * 1. the idea is that the file should be viewed as a stream or array of bytes
 * 2. the array of bytes stored in the file is indexed from 0 to len-1
 * 3. the file has 2 positions:
 * 		* Reading position: index of the next byte that will be read
 * 		* Writing position: index of the next byte where the output byte will be placed
 * 		* (both of these positions are independent; they can point in different positions)
 */

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <cstddef>

int main()
{
	// writing to a binary file 
	std::ofstream outfile{ "assets/out.dat", std::ios::binary };
	std::array<char, 5> data{ 1, 2, 3, 4, 5 };
	outfile.write(data.data(), 5);
	if (!outfile)
	{
		std::cerr << "Error writing to file\n";
		return -1;
	}
	outfile.close();

	// reading from a binary file
	// using iterators
	std::ifstream infile{ "out.dat", std::ios::binary };
	std::vector<char> inData{std::istreambuf_iterator<char>{infile}, {}};
	for (auto& d : inData)
		std::cout << static_cast<int>(d) << '\n';
	infile.close();

	// using read()
	// first seek to the end of the file
	infile.open("assets/out.dat", std::ios::ate | std::ios::binary);

	if (!infile)
	{
		int numBytesRead = infile.gcount();
		std::cerr << "Error opening file\n" 
				  << "Number of bytes read = " << numBytesRead << '\n'; 
		return -1;
	}

	const size_t fileSize = infile.tellg();
	std::vector<char> inData2(fileSize);
	infile.read(inData2.data(), fileSize);

	for (auto& d : inData)
		std::cout << static_cast<int>(d) << '\n';
	
	infile.close();
	std::cin.get();
}