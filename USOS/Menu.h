#pragma once
#include <iostream>

class Menu
{
public:
	static void show_main_menu()
	{
		std::cout << "USOS 2.0" << std::endl;
		std::cout << "1.Pokaz/edytuj element (by id)" << std::endl;
		std::cout << "2.Dodaj element" << std::endl;
		std::cout << "3.Zapisz do pliku" << std::endl;
		std::cout << "4.Wczytaj z pliku" << std::endl;
		std::cout << "5.Wyjscie" << std::endl;
		std::cout << "Wybierz opcje: " << std::endl;
	}

	static void show_choose_element()
	{
		std::cout << "1.Wykladowca" << std::endl;
		std::cout << "2.Student" << std::endl;
		std::cout << "3.Przedmiot" << std::endl;
		std::cout << "4.Powrot" << std::endl;
		std::cout << "Wybierz opcje: " << std::endl;
	}

	static void show_add_result(std::string result)
	{
		std::cout << "Status: "<< result << std::endl;
		std::cout << "1.Menu glowne" << std::endl;
		std::cout << "Wybierz opcje: " << std::endl;
	}

	static void show_details(Database* database, std::string command)
	{
		unsigned int option = std::stoi(command.substr(0,1)), id = std::stoi(command.replace(0, 1, ""));
		if(option == 1)
		{
			auto lecturer = database->get_lecturer_by_id(id);
			std::cout << "ID: " << lecturer.id_ << std::endl;
			std::cout << "Imie: " << lecturer.first_name_ << std::endl;
			std::cout << "Nazwisko: " << lecturer.last_name_ << std::endl;
			std::cout << "Prowadzone przedmioty: " << std::endl;
			for(auto id_subject : lecturer.id_subjects_)
			{
				auto subject = database->get_subject_by_id(id_subject);
				std::cout << "\t" << "ID: " << subject.id_ << std::endl;
				std::cout << "\t  " << "Nazwa: " << subject.name_ << std::endl;
				std::cout << "\t  " << "Zapisanych studentow: " << subject.id_students_.size() << std::endl;
			}
			std::cout << std::endl;
			std::cout << "1.Edytuj imie (not implemented)" << std::endl;
			std::cout << "2.Edytuj nazwisko (not implemented)" << std::endl;
			std::cout << "3.Usun" << std::endl;
			std::cout << "4.Powrot" << std::endl;
			std::cout << "Wybierz opcje: " << std::endl;
		}

		
	}
	
};

