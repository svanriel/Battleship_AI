#pragma once

#include <stdlib.h>
#include <time.h>
#include "Player.h"

class AI : public Player
{
protected:
	vector<Ship*> shipsToBeFound = Ship::getDefaultShipVector();

	//**MOVE**
	//This function performs a move for the AI, here just random
	//override this in any AI
	virtual void determineMove(int(&moveArray)[2]) override
	{
		do {
			moveArray[0] = rand() % 10;
			moveArray[1] = rand() % 10;	    
		} while (Player::grid_p[moveArray[0]][moveArray[1]] != 0);
	}
	
	

public: 
	//constructor, does really not much
	AI::AI() : Player()
	{
		srand(time(NULL));

		Player::playerIsRealPlayer = false;
		
		//initialize grid!
		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				Player::grid_p[x][y] = 0;
				Player::setup_p[x][y] = 0;
			}
		}
	}
	
	//explore any options around the point that was shot at
	virtual void exploreOptions(int* moveArray){}

	//look at any options found. returns true if success and inserts option found in moveArray. returns false if no options were found
	virtual bool exploitOptions(int(&moveArray)[2]){ return false; }
};