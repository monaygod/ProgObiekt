#include "rowerzysta.h"

#include <utility>

rowerzysta::rowerzysta(std::string _imie, std::string _nazwisko, std::string _adres, std::string _typ_roweru) :
	osoba(std::move(_imie), std::move(_nazwisko), std::move(_adres)),
	typ_roweru_(std::move(_typ_roweru))
{
}


std::string rowerzysta::to_string()
{
	return std::string("rowerzysta " + osoba::to_string() + " rower: " + typ_roweru_);
}
