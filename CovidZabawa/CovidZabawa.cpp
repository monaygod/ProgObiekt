#include <fstream>
#include <iostream>
#include <vector>


#include "Rekord.h"

int countFreq(std::string& pat, std::string& txt)
{
	int M = pat.length();
	int N = txt.length();
	int res = 0;

	/* A loop to slide pat[] one by one */
	for (int i = 0; i <= N - M; i++)
	{
		/* For current index i, check for
		   pattern match */
		int j;
		for (j = 0; j < M; j++)
			if (txt[i + j] != pat[j])
				break;

		// if pat[0...M-1] = txt[i, i+1, ...i+M-1] 
		if (j == M)
		{
			res++;
			j = 0;
		}
	}
	return res;
}


int main()
{
	std::vector<Rekord> rekordy;
	{
		std::fstream plik;
		std::string name, dna="", line;
		plik.open("sequences.fasta", std::ios::in);
		std::getline(plik, line);
		name = line;
		while (std::getline(plik, line))
		{
			if (line[0] == '>')
			{
				rekordy.emplace_back(name, dna);
				name = line;
				dna = "";
				continue;
			}
			dna += line;
		}
		rekordy.emplace_back(name, dna);
	}

	for(auto& rekord : rekordy)
	{
		//rekord.walidacja();
		rekord.kalkualtor();
		rekord.pokaz_rezultat();
	}


	
	
}