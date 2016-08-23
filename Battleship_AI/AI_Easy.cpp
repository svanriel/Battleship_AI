#pragma once

#include "AI.h"

using namespace std;

//This new class should override every function we would like to make in the AI
//so we can make and compare new AIs without changing the main class or program ;)
//We only need to change AI to AI_Easy (in this case)

class AI_Easy : public AI
{
	
protected:

	vector<int> xoptions = vector<int>();
	vector<int> yoptions = vector<int>();

public:

	AI_Easy::AI_Easy() { }

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
	virtual void exploreOptions(int* moveArray) override {
		int x = moveArray[0];
		int y = moveArray[1];
		//if not yet looked at
		if (grid_p[x][y] == 2) {
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

	//look at any options found. returns true if success and inserts option found in moveArray. returns false if no options were found
	bool exploitOptions(int(&moveArray)[2]) override {
		//if no options: return false
		if (xoptions.size() == 0) { return false; }

		//pick random option
		int n = rand() % xoptions.size();
		moveArray[0] = xoptions.at(n); //use at method for safety: operator[] is not safe, even when size() was used, especially when using erase
		moveArray[1] = yoptions.at(n);
		//erase element (and duplicates if any)
		for (int i = xoptions.size() - 1; i > -1; i--){
			if (xoptions.at(i) == moveArray[0] && yoptions.at(i) == moveArray[1]){ //here too
				xoptions.erase(xoptions.begin() + i);
				yoptions.erase(yoptions.begin() + i);
			}
		}
		return true;
	}

protected:
	virtual void determineMove(int(&moveArray)[2]) override
	{
		//look at poi's
		if (exploitOptions(moveArray)){ return; }
		//else do random move
		do {
			moveArray[0] = rand() % 10;
			moveArray[1] = rand() % 10;
		} while (grid_p[moveArray[0]][moveArray[1]] != 0);
	}
};