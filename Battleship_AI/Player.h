#pragma once

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include "Ship.h"

class Player
{
protected:
	//player is real player: true if real, false if AI
	bool playerIsRealPlayer;

	//binary array of own setup ('truth', where the ships are: 0 = no ship, 1 = ship but not yet hit, 2 = ship and hit)
	int setup_p[10][10];

	//array of guesses (note: grid_p are guesses by player on other player's setup: 0 = not yet guessed, 1 = guessed but no hit, 2 = guessed and hit)
	int grid_p[10][10];

	//array of all ships of the user
	vector<Ship*> ships = Ship::getDefaultShipVector();

	//**Determine next move**
	//overwrites a passed array
	//To be overwritten by implementing class
	virtual void determineMove(int(&moveArray)[2]){}

public:

	//constructor, does really not much
	Player::Player(){}

	//getters
	bool isRealPlayer(){ return playerIsRealPlayer; }
	vector<Ship*> getShips(){ return ships; }
	//get setup and grid
	int (&getSetup())[10][10] { return setup_p; }
	int(&getGrid())[10][10] { return grid_p; }

	//method determining if player has lost
	bool lost(){
		for (size_t i = 0; i < ships.size(); i++){
			if (!(ships.at(i)->getIsSunk())){ return false; } //not all ships are sunk yet
		}
		return true; //all ships sunk: player lost
	}

	//method determining if move was legal (i.e. was not at a place that was already shot at)
	bool isLegalMove(int *moveArray){
		return (!grid_p[moveArray[0]][moveArray[1]]);
	}

	//**SETUP**
	//To be overwritten by implementing class
	virtual void createSetup(){

		//randomly place ships one by one starting with the largest
		bool success = false;
		while (!success){
			//reset grid
			int shipsPlaced = 0;
			for (size_t i = 0; i < 10; i++){
				for (size_t j = 0; j < 10; j++){
					setup_p[i][j] = 0;
				}
			}
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
					int val1 = rand() % (10 - current->getSize() + 1);
					int val2 = rand() % (10);
					if (horizontal){
						x0 = val2;
						y0 = val1;
					}
					else{
						x0 = val1;
						y0 = val2;
					}

					//test if ship can be placed
					success = true;
					for (size_t j = 0; j < current->getSize(); j++){
						if (horizontal){
							if (setup_p[x0][y0 + j]){
								success = false;
								break;
							}
						}
						else{
							if (setup_p[x0 + j][y0]){
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
								setup_p[x0][y0 + j] = 1;
							}
							else{
								setup_p[x0 + j][y0] = 1;
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
		}//while no success
		//all ships successfully placed
	}

	//**MOVE**
	//returns an array {X,Y} of the next shot
	int(&move(int (&moveArray)[2]))[2]{
		determineMove(moveArray);
		return moveArray;
	}

	//**Method used when player is shot at**
	//input: an array {X,Y} of the other players trial shot
	//returns 0 when trial shot was a miss
	//returns 1 when trial shot was a hit
	//returns 2 when trial shot was a hit and the ship that was hit sank
	int trialShotAt(int moveArray[2]){
		size_t i = 0;
		int shootVal = 0;
		while (i < ships.size() && (shootVal == 0)){
			shootVal = ships.at(i)->shoot(moveArray[0], moveArray[1]);
			i++;
		}
		//now, the shootval is known (see above for what it means)
		//update the setup to indicate it has been shot
		if (shootVal!=0)
			setup_p[moveArray[0]][moveArray[1]] = 2; //this ship has now been hit
		return shootVal;
	}

	//**Method called after shot was done**
	//input param shootVal: 0 when missed, 1 when hit, 2 when hit and sunk
	//updates grid
	virtual void afterShot(int moveArray[2], int shootVal){
		if (shootVal != 0) //hit
			grid_p[moveArray[0]][moveArray[1]] = 2;
		else
			grid_p[moveArray[0]][moveArray[1]] = 1;
	}
};