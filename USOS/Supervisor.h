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
	Database main_database_;
	bool program_stop_flag = true;


public:
	void start()
	{
		state_ = State::MAIN_MENU;
		loop();		
	}
	void loop()
	{
		while (program_stop_flag)
		{
			system("cls");
			display();
			std::cin >> buffer;
			dispatch();
		}
	}

	void display()
	{
		switch (state_)
		{
		case State::MAIN_MENU: Menu::show_main_menu(); break;
		case State::ADD_MENU: Menu::show_choose_element(); break;
		case State::ADD_DETAILS: Menu::show_add_result(buffer); break;
		case State::SHOW_MENU: Menu::show_choose_element(); break;
		case State::SHOW_DETAILS: Menu::show_details(&main_database_, buffer); break;
		default:;
		}
	}

	void dispatch()
	{
		switch(state_)
		{
		case State::MAIN_MENU: dispatch_main_menu(); break;
		case State::ADD_MENU: dispatch_add_menu(); break;
		case State::ADD_DETAILS: dispatch_add_details(); break;
		case State::SHOW_MENU: dispatch_show_menu(); break;
		case State::SHOW_DETAILS: break;
		default: ;
		}
	}
	void dispatch_main_menu()
	{
		if(buffer == "1")
		{
			state_ = State::SHOW_MENU;
		}
		if (buffer == "2")
		{
			state_ = State::ADD_MENU;
		}
		if (buffer == "3")
		{
			//TODO zapis
			save_data();
		}
		if (buffer == "4")
		{
			//TODO wczytaj
			load_data();
		}
		if (buffer == "5")
		{
			program_stop_flag = false;
		}
	}
	void dispatch_add_menu()
	{
		if (buffer == "1") //wykladowca
		{
			system("cls");
			std::string first_name, last_name;
			std::cout << "Dodaj Wykladowce" << std::endl;
			std::cout << "Imie: ";
			std::cin >> first_name;
			std::cout << "Nazwisko: ";
			std::cin >> last_name;
			if (main_database_.add_lecturer(first_name, last_name))
				buffer = "Sukces";
			else
				buffer = "Blad";
			state_ = State::ADD_DETAILS;
		}
		if (buffer == "2") //student
		{
			system("cls");
			std::string first_name, last_name;
			std::cout << "Dodaj Studenta" << std::endl;
			std::cout << "Imie: ";
			std::cin >> first_name;
			std::cout << "Nazwisko: ";
			std::cin >> last_name;
			if (main_database_.add_student(first_name, last_name))
				buffer = "Sukces";
			else
				buffer = "Blad";
			state_ = State::ADD_DETAILS;
		}
		if (buffer == "3") //przedmiot
		{
			system("cls");
			std::string first_name, last_name;
			unsigned int id_lecturer;
			std::cout << "Dodaj Przedmiot" << std::endl;
			std::cout << "Nazwa: ";
			std::cin >> first_name;
			std::cout << "Opis: ";
			std::cin >> last_name;
			std::cout << "ID prowadzacego: ";
			std::cin >> id_lecturer;
			if (main_database_.add_subject(id_lecturer,first_name, last_name))
				buffer = "Sukces";
			else
				buffer = "Blad";
			state_ = State::ADD_DETAILS;
		}
		if (buffer == "4")
		{
			state_ = State::MAIN_MENU;
		}
	}
	void dispatch_add_details()
	{
		state_ = State::MAIN_MENU;
	}
	void dispatch_show_menu()
	{
		if (buffer == "1" || buffer == "2" || buffer == "3")
		{
			unsigned int id;
			system("cls");
			std::cout << "Podaj ID: ";
			std::cin >> id;
			buffer += std::to_string(id);
			state_ = State::SHOW_DETAILS;
		}
		if (buffer == "4")
		{
			state_ = State::MAIN_MENU;
		}
	}
	
	void save_data()
	{
		std::fstream plik;
		try {
			plik.open("save", std::ios::out | std::ios::binary);
			plik.write((char*)&main_database_, sizeof(main_database_));
			plik.close();
		}
		catch (std::exception e)
		{
			std::cout << e.what();
		}
	}
	void load_data()
	{
		std::fstream plik;
		try {
			plik.open("save", std::ios::in | std::ios::binary);;
			plik.read((char*)&main_database_, sizeof(Database));
			plik.close();
		}
		catch (std::exception e)
		{
			std::cout << e.what();
			std::system("pause");
		}
	}
};

