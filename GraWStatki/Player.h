#pragma once
#include "Board.h"
#include "HelpTools.h"

class Player
{
	Board my_ships;
	Board my_guesses;

public:
	virtual asd strzel(size_t x, size_t y);
	virtual bool UstawStatki();

	
};

