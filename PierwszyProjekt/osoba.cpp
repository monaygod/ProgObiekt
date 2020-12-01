#include "osoba.h"

#include <utility>

osoba::osoba(std::string _imie, std::string _nazwisko, std::string _adres) :
	imie_(std::move(_imie)),
	nazwisko_(std::move(_nazwisko)),
	adres_(std::move(_adres))
{

}

osoba::~osoba()
{
}

std::string osoba::to_string()
{
	return std::string(imie_ + " " + nazwisko_ + " " + adres_);
}
