#pragma once

#include <stdio.h>
#include <vector>

using namespace std;

class Ship
{
private:
	//int representing the size of the ship
	size_t size;

	//bool representing if ship is horizontal (true = horizontal, false = vertical)
	bool horizontal;

	//ints representing X and Y position of the most upper-left pixel of ship
	int X0;
	int Y0;

	//array representing the positions
	vector<int> positions;

	//bool representing if ship has already been sunk (0 = false, 1 = true -> das een boolean :P -> ok ja maar misschien wordt ie de magischerwijze de vliegende hollander, dat weet je niet)
	bool isSunk = false;

	//method to change 'float status' (isSunk) to 1
	void sink(){ isSunk = true; }

	//method to determine the status when hit
	//returns 0 when already hit at the same spot (and therefore not really hit)
	//returns 1 when hit but not yet sunk
	//returns 2 when hit and sunk
	int hit(int position){
		if (positions[position] == 1){ return 0; } //position already hit
		else{ positions[position] = 1; }
		//test if sunk
		for (size_t i = 0; i < size; i++){
			if (positions.at(i) == 0){ return 1; } //not yet sunk
		}
		//sunk
		sink();
		return 2;
	}
	
public:
	//default constructor with default values
	Ship::Ship() {}
	//default constructor with adjustable size
	Ship::Ship(size_t size){
		this->size = size;
		positions.resize(this->size);
	}
	//constructor
	Ship::Ship(size_t size, bool horizontal, int X0, int Y0) {
		this->size = size;
		this->horizontal = horizontal;
		this->X0 = X0;
		this->Y0 = Y0;
		positions.resize(this->size);
	}

	//getters
	size_t getSize(){ return size; }
	bool getHorizontal(){ return horizontal; }
	bool getIsSunk(){ return isSunk; }

	//method to be called during the initializing phase of the game: place the ships
	void place(bool horizontal, int X0, int Y0){
		this->horizontal = horizontal;
		this->X0 = X0;
		this->Y0 = Y0;
	}

	//method to test if ship is hit
	//returns 0 if not hit (missed)
	//returns 1 if hit
	//returns 2 if hit and sunk
	int shoot( int X, int Y ){
		if (isSunk){ return 0; } //sunk ships cannot be hit again (oh, really?)
		if (horizontal){
			if (Y != Y0){ return 0; } //not on the same line
			if ((X < X0) || (X >= X0 + size)){ return 0; } //too much to the left or right
			//hit
			return hit(X - X0);
		}
		else{
			if (X != X0){ return 0; } //not in the same collumn
			if ((Y < Y0) || (Y >= Y0 + size)){ return 0; } //too high or too low
			//hit
			return hit(Y - Y0);
		}
	}

	//returns default ship vector of (old system, default (no input param.)):
	//	1 ship of size 5
	//	2 ships of size 4
	//	4 ships of size 3
	//	2 ships of size 2
	//or (new system, input param. false):
	//	1 ship of size 5
	//	2 ships of size 4
	//	6 ships of size 3
	//	4 ships of size 2
	static vector<Ship*> getDefaultShipVector(bool old=true){
		if (old){ return vector<Ship*>({ new Ship(5), new Ship(4), new Ship(4), new Ship(3), new Ship(3), new Ship(3), new Ship(3), new Ship(2), new Ship(2) }); } // old system
		else{ return vector<Ship*>({ new Ship(5), new Ship(4), new Ship(4), new Ship(3), new Ship(3), new Ship(3), new Ship(3), new Ship(3), new Ship(3), new Ship(2), new Ship(2), new Ship(2), new Ship(2) }); } // new system
	}
}; 