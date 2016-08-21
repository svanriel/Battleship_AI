#pragma once

#include <stdlib.h>
#include <time.h>
#include "Player.h"

class RealPlayer : public Player
{
private:
	//**MOVE**
	//This function performs a move for a real player
	virtual void determineMove(int(&moveArray)[2]) override
	{
		//just take the inputs as move, so dont do anything here
	}

public:
	//constructor, does really not much
	RealPlayer::RealPlayer() : Player()
	{
		srand(time(NULL));

		Player::playerIsRealPlayer = true;

		//initialize grids!
		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				Player::grid_p[x][y] = 0;
				Player::setup_p[x][y] = 0;
			}
		}
		
	}

	//**SETUP**
	//create random setup
	virtual void createSetup() override { Player::createSetup(); }
};