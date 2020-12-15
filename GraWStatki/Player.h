#pragma once
#include "Board.h"
#include "HelpTools.h"

class Player
{
	Board my_ships;
	Board my_guesses;

public:
	Player(): my_ships(true)
	{
		
	}
	//virtual void strzel(size_t x, size_t y);
	void place_ship_randomly()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> place(0, 9);
		std::uniform_int_distribution<int> direction(0, 1);

		
		for(int i=0;i<ship_number;i++)
		{
			int x = place(gen), y = place(gen);
			bool dir= direction(gen);
			if (!my_ships.place_ship(i, dir, x, y))
				i--;
		}
	}

	void show_map()
	{
		auto a = my_ships.print_to_console();
		auto b = my_guesses.print_to_console();

		for (int i = 0; i < 11; i++)
		{
			std::cout << a[i] << "\t" << b[i] << std::endl;
		}
	}
	
};

