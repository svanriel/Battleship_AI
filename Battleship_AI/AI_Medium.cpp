#pragma once

#include "AI_Easy.cpp"
#include <array>

using namespace std;

//This class takes most of the AI_Easy class, but does some things smarter
//Additionally, some better data structures

class AI_Medium : public AI_Easy
{
protected:
	
	vector<std::array<int,2>> options; //options to be explored around hit
	//dan maar zo, BAM
	
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
		for (int size = 2; size < 6; size++) { //every size
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
							return;
						}
					}
				}
			}
		}
	}

public:
	
	AI_Medium::AI_Medium() { }

	vector<std::array<int, 2>> getOptions() { return options; }

	//check if there could be a hit at position [x,y] by checking whether a ship fits
	bool fits(int x, int y) {
		for (int size = 2; size < 6; size++) { //every size
			for (int shift = -size+1; shift < size; shift++) { //every shift [hit X X] to [X X hit]
				int sumH = 0;
				int sumV = 0;
				for (int i = 0; i < size; i++) { //test if a ship fits
					if (x - shift + i>-1 && x - shift + i < 10 && grid_p[x - shift + i][y] != 1) {
						sumH++;
					}
					if (y - shift + i>-1 && y - shift + i < 10 && grid_p[x][y - shift + i] != 1) {
						sumV++;
					}
				}
				if (sumH == size || sumV == size) {
					return true;
				}
			}
		}
		return false;
	}

	virtual void exploreOptions(int* moveArray){
		int x = moveArray[0];
		int y = moveArray[1];
		//if not yet looked at
		if (grid_p[x][y] == 2 && !seen[x][y]) {
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

		//pick random option
		int n = rand() % options.size();
		moveArray[0] = options.at(n)[0]; //use at method for safety: operator[] is not safe, even when size() was used, especially when using erase
		moveArray[1] = options.at(n)[1];
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
		}
		if (shootVal == 2){
			//ship was sunk, determine which one and remove it from the search list
			findSunkShip(moveArray);
		}
	}

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