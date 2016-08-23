#pragma once

#include <iostream>
#include <string>
#include "AI_Easy.cpp"
#include <array>

using namespace std;

//This class takes most of the AI_Easy class, but does some things smarter
//Additionally, some better data structures

class AI_Medium : public AI
{
protected:
	
	vector<std::array<int,2>> options; //options to be explored around hit
	//dan maar zo, BAM
	size_t minShipSize = 2;
	size_t maxShipSize = 5;

	//fields for preferenced direction
	int lastShot[2];
	size_t hitCounter = 0;
	bool lastShotWasHorizontal = true;
	int lastShotDirection = 0; // +1 for to the right or down, -1 for to the left or up
	bool lastShotWasHit = false;

	//check if a ship with size 'size' is still to be found
	bool shipRemains(int size) {
		//for all ships if ship with length size exists return true end return false
		for (int i = 0; i < shipsToBeFound.size(); i++) {
			if (shipsToBeFound.at(i)->getSize() == size)
				return true;
		}
		return false;
	}

	void findSunkShip(int* moveArray) {
		for (int size = maxShipSize-1; size >= minShipSize; size--) { //every size still to be accounted for
			for (int shift = -size + 1; shift < size; shift++) { //every shift [hit X X] to [X X hit]
				int sumH = 0;
				int sumV = 0;
				for (int i = 0; i < size; i++) { //test if a ship fits
					if (moveArray[0] - shift + i>-1 && moveArray[0] - shift + i < 10 && grid_p[moveArray[0] - shift + i][moveArray[1]] == 2) {
						sumH++;
					}
					if (moveArray[1] - shift + i>-1 && moveArray[1] - shift + i < 10 && grid_p[moveArray[0]][moveArray[1] - shift + i] == 2) {
						sumV++;
					}
				}
				if (sumH == size || sumV == size) {
					//find and remove the ship from the list
					for (int i = 0; i < shipsToBeFound.size(); i++) {
						if (shipsToBeFound.at(i)->getSize() == size) {
							shipsToBeFound.erase(shipsToBeFound.begin() + i);
							//adjust minShipSize and maxShipSize if neccessary
							if (minShipSize == size){
								minShipSize = shipsToBeFound.at(shipsToBeFound.size() - 1)->getSize();
							}
							else if (maxShipSize == size){
								maxShipSize = shipsToBeFound.at(0)->getSize();
							}
							return;
						}
					}
				}
			}
		}
	}

	virtual bool checkPreferencedDirection(int(&moveArray)[2]){
		bool prefWorked = false;
		if (hitCounter > 1 && lastShotDirection != 0){
			moveArray[0] = lastShot[0];
			moveArray[1] = lastShot[1];
			if (lastShotWasHit){
				if (lastShotWasHorizontal){
					if ((moveArray[0] + lastShotDirection < 10) && (moveArray[0] + lastShotDirection > -1)){ moveArray[0] += lastShotDirection; }
				}
				else if ((moveArray[1] + lastShotDirection < 10) && (moveArray[1] + lastShotDirection > -1)){ moveArray[1] += lastShotDirection; }
			}
			if (grid_p[moveArray[0]][moveArray[1]] == 0){ prefWorked = true; }
			else{ //try the other side
				if (lastShotWasHorizontal){
					if ((moveArray[0] - (hitCounter + 2)*lastShotDirection < 10) && (moveArray[0] + (hitCounter + 2)*lastShotDirection > -1)){
						moveArray[0] -= (hitCounter + 1)*lastShotDirection; 
					}
				}
				else if ((moveArray[1] - (hitCounter + 2)*lastShotDirection < 10) && (moveArray[1] + (hitCounter + 2)*lastShotDirection > -1)){ moveArray[1] -= (hitCounter + 1)*lastShotDirection; 
				}
				if (grid_p[moveArray[0]][moveArray[1]] == 0){
					prefWorked = true;
				}
				else{ //both sides didn't work => preferenced direction didn't work => reset
					if (!lastShotWasHit){
						hitCounter = 0;
					}
				}
			}
		}
		return prefWorked;
	}

	//tests if it is possible to place a ship of size 2 (prevents unnesseccary moves)
	bool surroundingAreAllMisses(int(&moveArray)[2]){
		int x = moveArray[0];
		int y = moveArray[1];
		if (x > 0){
			if (grid_p[x - 1][y] != 1){ return false; }
		}
		if (x < 9){
			if (grid_p[x + 1][y] != 1){ return false; }
		}
		if (y > 0){
			if (grid_p[x][y - 1] != 1){ return false; }
		}
		if (y < 9){
			if (grid_p[x][y + 1] != 1){ return false; }
		}
		return true;
	}

public:
	
	AI_Medium::AI_Medium() {
		lastShot[0] = 0;
		lastShot[1] = 0;  //ik flikker dit hier omdat het dan tenminste geen fucking kakerror geeft
	}

	vector<std::array<int, 2>> getOptions() { return options; }

	//check if there could be a hit at position [x,y] by checking whether a ship fits
	bool fits(int x, int y) {
			for (int shift = 0; shift <minShipSize; shift++) { //every shift [hit X X] to [X X hit]
				int sumH = 0;
				int sumV = 0;
				for (int i = 0; i < minShipSize; i++) { //test if a ship fits
					if (x - shift + i>-1 && x - shift + i < 10 && grid_p[x - shift + i][y] != 1) {
						sumH++;
					}
					if (y - shift + i>-1 && y - shift + i < 10 && grid_p[x][y - shift + i] != 1) {
						sumV++;
					}
				}
				if (sumH == minShipSize || sumV == minShipSize) {
					return true;
				}
			}
	return false;
	}

	virtual void exploreOptions(int* moveArray){
		int x = moveArray[0];
		int y = moveArray[1];
		//if not yet looked at
		if (grid_p[x][y] == 2) {
			//yay hardcoding	
			if (x - 1 > -1 && grid_p[x - 1][y] == 0 && fits(x-1,y) ){
				std::array<int, 2> temp = { x - 1, y };
				options.push_back(temp);
			}
			if (x + 1 < 10 && grid_p[x + 1][y] == 0 && fits(x+1,y)){
				std::array<int, 2> temp = { x + 1, y };
				options.push_back(temp);
			}
			if (y - 1 > -1 && grid_p[x][y - 1] == 0 && fits(x,y-1)){
				std::array<int, 2> temp = { x, y - 1 };
				options.push_back(temp);
			}
			if (y + 1 < 10 && grid_p[x][y + 1] == 0 && fits(x,y+1)){
				std::array<int, 2> temp = { x, y + 1 };
				options.push_back(temp);
			}
		}
	}

	bool exploitOptions(int(&moveArray)[2]) {
		//if no options: return false
		if (options.size() == 0) { return false; }

		//use preferenced direction
		if (!checkPreferencedDirection(moveArray)){
			//pick random option
			int n = rand() % options.size();
			moveArray[0] = options.at(n)[0]; //use at method for safety: operator[] is not safe, even when size() was used, especially when using erase
			moveArray[1] = options.at(n)[1];
		}

		//erase element (and duplicates if any)
		for (int i = options.size() - 1; i > -1; i--){
			if (options.at(i)[0] == moveArray[0] && options.at(i)[1] == moveArray[1]) //here too
				options.erase(options.begin() + i);
		}
		return true;
	}

	virtual void afterShot(int moveArray[2], int shootVal) override {
		Player::afterShot(moveArray, shootVal);
		if (shootVal == 1){
			//ship was found but not sunk: worth looking into
			exploreOptions(moveArray);
			hitCounter++;
			lastShotWasHit = true;
		}
		else if (shootVal == 2){
			//ship was sunk, determine which one and remove it from the search list
			findSunkShip(moveArray);
			//reset hitCounter
			hitCounter = 0;
			lastShotWasHit = false;
		}
		else{ 
			if (!lastShotWasHit){
				hitCounter = 0;
			}
			else{
				//else try preferenced again on the opposite side (if preferenced direction is used)
				lastShotWasHit = false;
			}
		} //reset hitCounter

		//update preferenced direction
		int xDiff = moveArray[0] - lastShot[0];
		int yDiff = moveArray[1] - lastShot[1];
		if (xDiff == 0 && (yDiff == -1 || yDiff == 1)){
			lastShotWasHorizontal = false;
			lastShotDirection = yDiff;
		}
		else if (yDiff == 0 && (xDiff == -1 || xDiff == 1)){
			lastShotWasHorizontal = true;
			lastShotDirection = xDiff;
		}
		else{
			lastShotDirection = 0;
		}
		lastShot[0] = moveArray[0];
		lastShot[1] = moveArray[1];
	}

protected:
	virtual void determineMove(int(&moveArray)[2]) override
	{
		//look at poi's
		if (!exploitOptions(moveArray)){
			//else do random move
			do {
				moveArray[0] = rand() % 10;
				moveArray[1] = rand() % 10;
			} while (grid_p[moveArray[0]][moveArray[1]] != 0 && !surroundingAreAllMisses(moveArray));
		}
	}

};