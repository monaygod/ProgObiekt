/*
2) Baza danych podobna do USOSa tzn.
wystêpuj¹ studenci, nauczyciele, zajêcia, oceny z poszczególnych zajêæ
(nie jedna ale mo¿liwoœæ wielu ocen).
Funkcjonalnoœæ:
1) dodawanie i usuwanie wszystkich wspomnianych wy¿ej elementów
2) zapisywanie i odczytywanie bazy z pliku.
3) Wsywietlanie (oczywiœcie na ¿¹danie) odpowiednich elementów z bazy
4) Menu zawieraj¹ce wszystkie te funkcjonalnoœci.
*/

#pragma once
#include <list>

#include "osoba.h"


class Repo
{
	std::list<osoba*> data_;
	// std::list<zajecia???> zajecia_;
	// std::list<oceny?> oceny_;
	
	/*
	 * relacje?
	 * student W:W zajecia
	 * zajecia 1:W nauczyciel
	 * zajecia W:W student
	 * ocena 1:W student
	 */
	
public:
	/*
	 * TODO
	 * read_from_file(filename, path)
	 * save_to_file(filename, path)
	 * add(osoba* c)
	 * remove
	 * 
	 */
	
};

