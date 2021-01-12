#pragma once
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
			std::cout << a.first << ":" << a.second;
			if(ilosc == 4)
			{
				std::cout << std::endl;
				ilosc = 0;
			}
			else
			{
				ilosc++;
				std::cout << "    \t";
			}
		}
	}



	
};

