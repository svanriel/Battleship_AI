#pragma once

#include <stdlib.h>
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

	//**SETUP**
	//To be overwritten by implementing class
	virtual void createSetup() = 0;

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
	void afterShot(int moveArray[2],int shootVal){		
		if (shootVal != 0) //hit
			grid_p[moveArray[0]][moveArray[1]] = 2;
		else
			grid_p[moveArray[0]][moveArray[1]] = 1;
	}
};