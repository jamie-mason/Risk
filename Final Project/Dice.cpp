#include<iostream>
#include"Dice.h"


int Dice::roll() {
	return rand() % 6 + 1;
	//returns a random number between 1 and 6 like a standard die would;
}
