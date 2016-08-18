#pragma once

#include <stdlib.h>
#include <time.h>
#include "Player.h"

class AI : public Player
{
private:	
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

	//**SETUP**
	//create random setup
	virtual void createSetup(){
		//randomly place ships one by one starting with the largest
		bool success = false;
		while (!success){
			int shipsPlaced = 0;
			for (size_t i = 0; i < ships.size(); i++){
				//parameter determining if ship has been successfully placed
				success = false;
				//counter determining if failrate is too high (hinting for an unsolvable setting)
				int failCounter = 0;
				//current ship to be placed
				Ship* current = ships.at(i);
				//ship position parameters
				bool horizontal;
				int x0, y0;

				//try to place ship
				while (!success){
					//generate random position
					horizontal = rand() % 2;
					int val1 = rand() % (10 - current->getSize());
					int val2 = rand() % (10);
					if (horizontal){
						x0 = val1;
						y0 = val2;
					}
					else{
						x0 = val2;
						y0 = val1;
					}

					//test if ship can be placed
					success = true;
					for (size_t j = 0; j < current->getSize(); j++){
						if (horizontal){
							if (Player::setup_p[x0][y0 + j]){
								success = false;
								break;
							}
						}
						else{
							if (Player::setup_p[x0 + j][y0]){
								success = false;
								break;
							}
						}
					}

					if (success){
						//ship was placed successfully
						//update ship placement parameters
						current->place(!horizontal, x0, y0); 
						shipsPlaced++;
						//update grid
						for (size_t j = 0; j < current->getSize(); j++){
							if (horizontal){
								Player::setup_p[x0][y0 + j] = 1;
							}
							else{
								Player::setup_p[x0 + j][y0] = 1;
							}
						}
					}
					else{
						//ship placing failed
						failCounter++;
						if (failCounter >= 100){ break; } //convergence not reached
					}
				}
				if (failCounter >= 100){ break; } //convergence not reached: start over
			}//for ships			
		}//while success
		//all ships successfully placed
	}
};