#pragma once
#include "osoba.h"
class rowerzysta : public osoba
{
protected:
	std::string typ_roweru_;

public:
	rowerzysta(std::string _imie, std::string _nazwisko, std::string _adres, std::string _typ_roweru);

	std::string to_string();
};

