#include "zajecia_1.h"


#include <iomanip>
#include <iostream>

struct mojaStruktura
{
	int jeden;
	int dwa;
	int trzy;
};
typedef mojaStruktura ms;


void funkcjadowolna(ms& data)
{
	data.dwa += 3;
}

void zajecia_1::do_something()
{
#pragma region zadanie1
	int* tablica = new int[100];

	for (int i = 1; i <= 100; i++)
	{
		tablica[i - 1] = i;
	}
	std::cout << std::setw(3);

	for (int i = 0; i < 100; i += 5)
	{
		for (int j = i; j < i + 5; j++)
		{
			std::cout << std::setw(3) << tablica[j] << " ";
		}
		std::cout << std::endl;
	}
#pragma endregion

#pragma region zadanie2

	ms* nowaZmienna = new ms();

	nowaZmienna->jeden = 1;
	nowaZmienna->dwa = 2;
	nowaZmienna->trzy = 3;

	std::cout << "Przed: \t" << std::setw(2) << nowaZmienna->jeden << " " << std::setw(2) << nowaZmienna->dwa << " " << std::setw(2) << nowaZmienna->trzy << std::endl;

	funkcjadowolna(*nowaZmienna);

	std::cout << "Po: \t" << std::setw(2) << nowaZmienna->jeden << " " << std::setw(2) << nowaZmienna->dwa << " " << std::setw(2) << nowaZmienna->trzy << std::endl;

#pragma endregion

#pragma region zadanie3

	int** tab = new int* [20];
	for (int i = 0; i < 20; i++)
	{
		tab[i] = new int[5];
	}


	for (int i = 0; i < 20; i++)
	{
		delete[]tab[i];
	}
	delete[]tab;


#pragma endregion
}
