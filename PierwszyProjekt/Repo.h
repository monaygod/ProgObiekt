/*
2) Baza danych podobna do USOSa tzn.
wyst�puj� studenci, nauczyciele, zaj�cia, oceny z poszczeg�lnych zaj��
(nie jedna ale mo�liwo�� wielu ocen).
Funkcjonalno��:
1) dodawanie i usuwanie wszystkich wspomnianych wy�ej element�w
2) zapisywanie i odczytywanie bazy z pliku.
3) Wsywietlanie (oczywi�cie na ��danie) odpowiednich element�w z bazy
4) Menu zawieraj�ce wszystkie te funkcjonalno�ci.
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

