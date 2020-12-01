#pragma once
#include <string>

class osoba
{
protected:
	std::string imie_;
	std::string nazwisko_;
	std::string adres_;

public:
	osoba(std::string _imie, std::string _nazwisko, std::string _adres);
	~osoba();

	virtual std::string to_string();
	
	
};

