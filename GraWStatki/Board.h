#pragma once
#include <iomanip>
#include <random>
#include <list>
#include <sstream>
#include <string>
#include <vector>


#include "HelpTools.h"
#include "Punkt.h"
#include "Ship.h"
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
	~Board()
	{
		for (size_t i=0;i<size_*size_;i++)
			delete tablica[i];
		delete[] tablica;
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
			result_temp[i+1] << std::right << std::setw(nameWidth) << std::setfill(separator) << i ;
			for (size_t j = 0; j < size_; j++)
			{
				result_temp[i + 1] << std::right << std::setw(nameWidth) << std::setfill(separator) << (*this)(i,j)->to_string();
			}
		}

		std::string* result = new std::string[size_ + 1];
		for (size_t i = 0; i < size_ + 1; i++)
			result[i] = result_temp[i].str();
		
		return result;
	}

	bool place_ship(int ship_id, bool ship_direction, size_t x, size_t y)
	{
		
		for(int i=0;i<ship_table[ship_id];i++)
		{
			int x_next = x, y_next = y;
			if (ship_direction)
				x_next += i;
			else
				y_next += i;

			if (x_next >= size_ || y_next >= size_)
				return false;
			
			if (typeid(*((*this)(x_next, y_next))) != typeid(Water))
				return false;
		}
		for (int i = 0; i < ship_table[ship_id]; i++)
		{
			int x_next = x, y_next = y;
			if (ship_direction)
				x_next += i;
			else
				y_next += i;
			
			delete (*this)(x_next, y_next);
			(*this)(x_next, y_next) = new Ship(show_ship);
		}
		return true;
	}

	void swap_to_ship(size_t x, size_t y)
	{
		delete (*this)(x, y);
		(*this)(x, y) = new Ship(show_ship);
	}

	Punkt*& operator()(int x, int y)
	{
		return tablica[x * size_ + y];
	}

};

