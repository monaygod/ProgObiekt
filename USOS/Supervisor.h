#pragma once
#include <fstream>
#include <string>


#include "Database.h"
#include "Menu.h"
enum class State
{
	MAIN_MENU,
	ADD_MENU,
	ADD_DETAILS,
	SHOW_MENU,
	SHOW_DETAILS
};

class Supervisor
{
	State state_;
	std::string buffer;
	unsigned int temp_int_1 = 0, temp_int_2 = 0;
	Database main_database_;
	bool program_stop_flag = true;


public:
	void start();

private:
	void loop();

	void display();

	void dispatch();

	void dispatch_main_menu();

	void dispatch_add_menu();

	void dispatch_add_details();

	void dispatch_show_menu();

	void dispatch_show_details();

	void save_data();

	void load_data();
};

