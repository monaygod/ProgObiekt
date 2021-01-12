#pragma once
#include "Board.h"
#include "HelpTools.h"

class Player
{
protected:
	Board my_ships;
	Board my_guesses;

public:
	Player(): my_ships(true), my_guesses(true)
	{
		
	}
	~Player() = default;
	bool under_fire(size_t x, size_t y)
	{
		my_ships(x, y)->hit = true;
		std::cout << typeid(*my_ships(x, y)).name(); //to musi tutaj być bo inaczej if nie działa. czemu?
		if (typeid(*my_ships(x, y)) == typeid(Ship))
			return true;
		return false;
	}
	virtual void fire(size_t x, size_t y, Player* opponent) = 0;
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

	Board get_my_ships()
	{
		return my_ships;
	}
	Board get_my_guesses()
	{
		return my_guesses;
	}
	
};

