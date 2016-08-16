
#include "AI.h"

//This new class should override every function we would like to make in the AI
//so we can make and compare new AIs without changing the main class or program ;)
//We only need to change AI to AI_Easy (in this case)

class AI_Easy : public AI
{
public:

	void move(int grid[10][10], int setup[10][10])
	{
		//this is the challenge :P
	}
};