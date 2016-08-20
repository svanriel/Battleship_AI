
#include "AI.h"

//This new class should override every function we would like to make in the AI
//so we can make and compare new AIs without changing the main class or program ;)
//We only need to change AI to AI_Easy (in this case)

class AI_Easy : public AI
{
	
protected:

	bool seen[10][10];
	vector<Ship*> shipsToBeFound = Ship::getDefaultShipVector();

public:

	AI_Easy::AI_Easy() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				seen[i][j] = false;
			}
		}
	}

	virtual void determineMove(int(&moveArray)[2]) override
	{
		vector<int> xoptions;
		vector<int> yoptions;

		//1. look for newly discovered hits
		for (int y = 0; y < 10; y++) {
			for (int x= 0; x < 10; x++) {
				
				//if not yet looked at
				if (grid_p[x][y] == 2 && !seen[x][y]) {

					//yay hardcoding					
					int x0=x;
					int y0=y;
					if (x - 1>-1 && grid_p[x - 1][y] != 1)
						x0 =  x - 1;
					else if (x + 1<10 && grid_p[x + 1][y] != 1)
						x0 = x + 1;
					else if (y - 1>-1 && grid_p[x][y-1] != 1)
						y0 = y-1 ;
					else if (y + 1<10 && grid_p[x][y+1] != 1)
						y0 = y+1;
					if (x0 != x || y0 != y){ //uuugh, WHYYYY					
						xoptions.push_back(x0);
						yoptions.push_back(y0);
					}
					//take a random option
					if (xoptions.size() > 0) {
						int n = rand() % xoptions.size();					
						moveArray[0] = xoptions[n];
						moveArray[1] = yoptions[n];
						//easy for now: when you have seen every square around a hit, don't look at it again
						if (xoptions.size()==1)
							seen[moveArray[0]][moveArray[1]] = true;
						return;
					}

				}
			}
		}
		//else do random move
		do {
			moveArray[0] = rand() % 10;
			moveArray[1] = rand() % 10;
		} while (grid_p[moveArray[0]][moveArray[1]] != 0);

	}
};