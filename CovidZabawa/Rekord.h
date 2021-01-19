#pragma once
#include <iomanip>
#include <string>
#include <map>

static std::string znaczki = "AGTC";

class Rekord
{
	std::string nazwa;
	std::string dna;
	std::map< std::string, unsigned int> mapa;

public:
	Rekord(std::string name, std::string value) : nazwa(name), dna(value)
	{
		
	}

	void walidacja()
	{
		int dna_len = dna.length()-1;
		for (int i = 0; i < dna_len; i++)
		{
			if (znaczki.find(dna[i])==std::string::npos)
			{
				dna.erase(i);
				i--;
				dna_len--;
			}
		}
	}

	void kalkualtor()
	{
		for(int i=0;i<dna.length()-2;i++)
		{
			std::string literka(1, dna[i]);
			std::string literki(1, dna[i]);
			literki += dna[i + 1]; literki += dna[i + 2];
			mapa[literka]++;
			mapa[literki]++;
		}
		for (int i = dna.length() - 2; i < dna.length(); i++)
		{
			std::string literka(1, dna[i]);
			mapa[literka]++;
		}
	}

	void pokaz_rezultat()
	{
		std::cout << nazwa << std::endl;
		int ilosc = 0;
		for(auto a : mapa)
		{
			
			if(!check(znaczki,a.first))
			{
				continue;
			}
			std::cout << std::right << std::setw(4) << std::setfill(' ') << a.first << ":" << std::left << std::setw(7) << std::setfill(' ') << a.second;
			if(ilosc == 4)
			{
				std::cout << std::endl;
				ilosc = 0;
			}
			else
			{
				ilosc++;
			}
		}
		std::cout << std::endl;
	}

	bool check(std::string s1, std::string s2)
	{
		for(auto a: s2)
		{
			if (s1.find(a) == std::string::npos)
			{
				return false;
			}
		}
		return true;
	}


	
};

