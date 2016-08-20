#pragma once


#include "AI.h"

using namespace std;

//This new class should override every function we would like to make in the AI
//so we can make and compare new AIs without changing the main class or program ;)
//We only need to change AI to AI_Easy (in this case)

class AI_Easy : public AI
{
	
protected:

	bool seen[10][10];
	vector<Ship*> shipsToBeFound = Ship::getDefaultShipVector();
	vector<int> xoptions = vector<int>();
	vector<int> yoptions = vector<int>();

public:

	AI_Easy::AI_Easy() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				seen[i][j] = false;
			}
		}
	}

	vector<int> getXOptions(){ return xoptions; }
	vector<int> getYOptions(){ return yoptions; }

	virtual void afterShot(int moveArray[2], int shootVal) override {
		Player::afterShot(moveArray, shootVal);
		if (shootVal == 1){
			//ship was found but not sunk: worth looking into
			exploreOptions(moveArray);
		}
	}

	//explore any options around the point that was shot at
	void exploreOptions(int* moveArray){
		int x = moveArray[0];
		int y = moveArray[1];
		//if not yet looked at
		if (grid_p[x][y] == 2 && !seen[x][y]) {
			//yay hardcoding	
			if (x - 1>-1 && grid_p[x - 1][y] == 0){
				xoptions.push_back(x - 1);
				yoptions.push_back(y);
			}
			if (x + 1 < 10 && grid_p[x + 1][y] == 0){
				xoptions.push_back(x + 1);
				yoptions.push_back(y);
			}
			if (y - 1 > -1 && grid_p[x][y - 1] == 0){
				xoptions.push_back(x);
				yoptions.push_back(y - 1);
			}
			if (y + 1 < 10 && grid_p[x][y + 1] == 0){
				xoptions.push_back(x);
				yoptions.push_back(y + 1);
			}
		}
	}

	virtual void determineMove(int(&moveArray)[2]) override
	{
		//1. look for newly discovered hits
		//take a random option
		if (xoptions.size() > 0) {
			int n = rand() % xoptions.size();
			moveArray[0] = xoptions[n];
			moveArray[1] = yoptions[n];
			//erase element (and duplicates if any)
			for (int i = xoptions.size() - 1; i > -1; i--){
				if (xoptions[i] == moveArray[0] && yoptions[i] == moveArray[1]){
					xoptions.erase(xoptions.begin() + i);
					yoptions.erase(yoptions.begin() + i);
				}
			}

			//DEBUG: easy for now: when you have seen every square around a hit, don't look at it again => remove
			if (xoptions.size() == 0){
				seen[moveArray[0]][moveArray[1]] = true;
			}
			return;
		}

		//else do random move
		do {
			moveArray[0] = rand() % 10;
			moveArray[1] = rand() % 10;
		} while (grid_p[moveArray[0]][moveArray[1]] != 0);

	}
};