#include <iostream>
#include <fstream>

/*
 * argc is the argument count
 * it is the number of arguments passed into the program from the
 * command line
 
 * the array of character pointers is the listing of all the arguments. 
 * argv[0] is the command with which the program is invoked
 * not available. 
 * After that every element number less than argc is a command line 
 * argument. 
 * argv can be used as a string or a two dimensional array.
 */

int main(int argc, char* argv[])
{
	if (argc != 2) // argc should be 2 for correct execution
		// Print argv[0] assuming it is the program name
		std::cout << "usage: " << argv[0] << std::endl;
	else{
		std::ifstream theFile(argv[1]);
		if(!theFile.is_open())
			std::cout << "Could not open the file\n";
		else
		{
			char x;
			// prints the contents of theFile
			while(theFile.get(x))
				std::cout << x;
		}
	}
	std::cin.get();
	return 0;
}