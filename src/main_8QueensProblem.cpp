#include<iostream>

#define BOARDSIZE 8
#define DIAGONAL (2 * BOARDSIZE - 1)
#define DOWNOFFSET (BOARDSIZE - 1)

void AddQueen(bool showBoard = true);
void WriteBoard(bool showBoard = true);

int queencol[BOARDSIZE]; // column with the queen
bool colfree[BOARDSIZE]; // is the columm free?
bool upfree[DIAGONAL];   // is the upward diagonal free?
bool downfree[DIAGONAL]; // is the downward diagonal free?

int  queencount    = -1; // row whose queen is currently placed
int  funcCallCount = 0;  // no. of times AddQueen() is called
int  numsol    = 0;      // number of solutions found
bool solFound  = false;  // set this to true in WriteBoard() definition to only view the first solution(i.e, only one solution)
bool showBoard = true;   // display all solutions

int main()
{
	std::cout << "N Queens Problem\n"
			  << "For " << BOARDSIZE << "x" << BOARDSIZE << '\n';

	for (int i = 0; i < BOARDSIZE; i++)
		colfree[i]  = true;
	for (int i = 0; i < DIAGONAL; i++)
	{
		upfree[i]   = true;
		downfree[i] = true;
	}

	AddQueen(showBoard);
	std::cout << "Number of solutions found = " << numsol << '\n';

	//std::cin.get();
	return 0;
}


void AddQueen(bool showBoard)
{
	int col;		//column being tried for the queen
	queencount++;
	for (col = 0; col < BOARDSIZE; col++)
	{
		if (colfree[col] && upfree[queencount + col] && downfree[queencount - col + DOWNOFFSET])//put a queen in position (queencount, col)
		{
			queencol[queencount] = col;
			colfree[col] = false;
			upfree[queencount + col] = false;
			downfree[queencount - col + DOWNOFFSET] = false;
			
			if (queencount == BOARDSIZE - 1)	//termination condition
				WriteBoard(showBoard);
			else
				AddQueen(showBoard);				//proceed recursively

			colfree[col] = true;		//now backtracking by removing the queen
			upfree[queencount + col] = true;
			downfree[queencount - col + DOWNOFFSET] = true;
		}
	}
	queencount--;
}

void WriteBoard(bool showBoard)
{
	numsol++;
	if (!solFound && showBoard)
	{
		std::cout << "\n\t\tSolution " << numsol << '\n';
		for (int row = 0; row < BOARDSIZE; row++)
		{
			for (int col = 0; col < BOARDSIZE; col++)
			{
				if (col == queencol[row])
					std::cout << "\tQ";
				else
					std::cout << "\tx";
			}
			std::cout << '\n';
		}
	}
	solFound = false;
}