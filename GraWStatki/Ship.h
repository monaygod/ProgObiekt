#pragma once
#include <string>

#include "Punkt.h"
class Ship :
    public Punkt
{
public:
	Ship(bool _show_ship = false) : Punkt(false, _show_ship) {};
	std::string to_string()
	{
		
		return hit ? "x" : show_ship ? "#" : "_";
	}
};

