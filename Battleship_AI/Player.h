#pragma once

#include <stdlib.h>
#include <time.h>
#include "Ship.h"

class Player
{
protected:
	//binary array of own setup ('truth', where the ships are: 0 = no ship, 1 = ship but not yet hit, 2 = ship and hit)
	int setup_p[10][10];
	//array of guesses (note: grid_p are guesses by player on other player's setup: 0 = not yet guessed, 1 = guessed but no hit, 2 = guessed and hit)
	int grid_p[10][10];
	//array of all ships of the user
	Ship ships[];


public:

	//constructor, does really not much
	Player::Player()
	{
		srand(time(NULL));
		//see, not much...
	}


	//**MOVE**
	//To be overwritten by implementing class
	virtual void move(int grid[10][10], int setup[10][10]);


};