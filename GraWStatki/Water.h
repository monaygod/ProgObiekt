#pragma once
#include <string>

#include "Punkt.h"

class Water :
    public Punkt
{
public:
	Water(bool _show_ship = false) : Punkt(false, _show_ship) {};
	std::string to_string() override
	{
		
		return hit ? "o" : "_";
	}
};

