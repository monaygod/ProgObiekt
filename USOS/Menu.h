#pragma once
#include <iostream>
#include <string>

#include "Database.h"

class Menu
{
public:
	static void show_main_menu();

	static void show_choose_element();

	static void show_add_result(std::string result);

	static void show_details(Database* database, unsigned int, unsigned int);
};

