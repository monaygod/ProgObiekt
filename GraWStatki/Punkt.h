#pragma once
class Punkt
{
public:
	bool hit;
	bool show_ship;
	Punkt(bool _hit, bool _show_ship) : hit(_hit), show_ship(_show_ship){}
public:
	virtual std::string to_string() = 0;
	~Punkt() = default;
};

