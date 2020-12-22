#pragma once
#include "Player.h"
class Human :
    public Player
{
	void fire(size_t x, size_t y, Player* opponent)
	{
		if (opponent->under_fire(x, y)) {
			my_guesses.swap_to_ship(x, y);
		}
		my_guesses(x, y)->hit = true;		
	}
};

