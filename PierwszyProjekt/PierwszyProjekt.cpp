#include "Wielomian.h"
#include "osoba.h"
#include "rowerzysta.h"
#include <list>

auto main() -> int
{
	#pragma region Wielomian_tests
	auto* moj_obiekt = new Wielomian<double>("2x^40-5x^2+4x-2");
	auto* moj_obiekt2 = new Wielomian<double>("2x^2+3-1x^7");
	auto moj_obiekt3 = *moj_obiekt2;
	//std::cin >> moj_obiekt3;

	std::cout << moj_obiekt->to_string() << std::endl;
	std::cout << moj_obiekt->horner_wartosc(-3) << std::endl;
	std::cout << moj_obiekt2->to_string() << std::endl;
	std::cout << moj_obiekt3.to_string() << std::endl;
	std::cout << (*moj_obiekt + *moj_obiekt2).to_string() << std::endl;
	std::cout << (Wielomian<double>::horner_dzielenie(*moj_obiekt, -1).to_string()) << std::endl;
	

	moj_obiekt3.read_from_file("t.txt", 0);
	std::cout << moj_obiekt3.to_string() << std::endl;
	moj_obiekt2->save_to_file("aaaaaaa.txt");
	#pragma endregion Wielomian_tests



	#pragma region Baza_danych
	
	std::list<osoba*> lista;
	
	osoba x("a", "b", "c");
	rowerzysta y("a", "b", "c", "gorski");

	lista.push_back(&x);
	lista.push_back(&y);

	for(auto &i : lista)
	{
		std::cout << (*i).to_string() << std::endl;
	}

	#pragma endregion Baza_danych


	return 0;
}
