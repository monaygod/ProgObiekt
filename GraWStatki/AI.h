#pragma once
#include "Player.h"
class AI :
    public Player
{
	void fire(size_t x, size_t y, Player* opponent)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> place(0, 9);

		x = place(gen);
		y = place(gen);
				
		if (opponent->under_fire(x, y)) {
			my_guesses.swap_to_ship(x, y);
		}
		my_guesses(x, y)->hit = true;
	}
};

