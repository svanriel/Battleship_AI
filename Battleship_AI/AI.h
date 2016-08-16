#pragma once

#include <stdlib.h>
#include <time.h>

class AI
{
public: 
	
	//constructor, does really not much
	AI::AI()
	{
		srand(time(NULL));
		//see, not much...
	}

	//**MOVE**
	//This function performs a move for the AI, here just random
	//override this in any AI
	//grid is both in- and output for this function (just change it inside)
	void move(int grid[10][10], int setup[10][10])
	{
		int x, y, n;
		do {
			x = rand() % 10;
			y = rand() % 10;	    
		} 
		while (grid[x][y] != 0);

		//set the guess, and we're done!
		if (setup[x][y] == 1)
			grid[x][y] = 2;
		else
			grid[x][y] = 1;

	}

};