#pragma once
#include <iomanip>
#include <random>
#include <list>
#include <sstream>
#include <string>
#include <vector>


#include "HelpTools.h"
#include "Punkt.h"
#include "Water.h"

class Board
{
	const size_t size_ = 10;
	Punkt** tablica;
	bool show_ship;
	

public:
	Board(bool _show_ship = false) : tablica(new Punkt* [size_ * size_]), show_ship(_show_ship)
	{
		for (size_t i = 0; i < size_ * size_; i++)
		{
			tablica[i] = new Water(show_ship);
		}
	}

	std::string* print_to_console()
	{
		const char separator = ' ';
		const int nameWidth = 2;
		std::ostringstream* result_temp = new std::ostringstream[size_+1];

		result_temp[0] << std::right << std::setw(nameWidth) << std::setfill(separator) << ' ';
		for (size_t j = 0; j < size_; j++)
		{
			result_temp[0] << std::right << std::setw(nameWidth) << std::setfill(separator) << char('A' + j);
		}

		for (int i = 0; i < size_; i++)
		{
			result_temp[i+1] << std::right << std::setw(nameWidth) << std::setfill(separator) << i + 1;
			for (size_t j = 0; j < size_; j++)
			{
				result_temp[i + 1] << std::right << std::setw(nameWidth) << std::setfill(separator) << tablica[i]->to_string();
			}
		}

		std::string* result = new std::string[size_ + 1];
		for (size_t i = 0; i < size_ + 1; i++)
			result[i] = result_temp[i].str();
		
		return result;
	}

	void place_ship_randomly()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, 10);

		
		for(const auto& a : ship_table)
		{
			std::cout << dis(gen);
		}
	}

	void place_ship(int ship_id, int ship_direction, size_t x, size_t y)
	{
		
	}

};

