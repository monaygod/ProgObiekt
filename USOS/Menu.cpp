#pragma once
#include "Menu.h"

#include <iostream>
#include <ostream>

void Menu::show_main_menu()
{
	std::cout << "USOS 2.0" << std::endl;
	std::cout << "1.Pokaz/edytuj element (by id)" << std::endl;
	std::cout << "2.Dodaj element" << std::endl;
	std::cout << "3.Zapisz do pliku" << std::endl;
	std::cout << "4.Wczytaj z pliku" << std::endl;
	std::cout << "5.Wyjscie" << std::endl;
	std::cout << "Wybierz opcje: " << std::endl;
}

void Menu::show_choose_element()
{
	std::cout << "1.Wykladowca" << std::endl;
	std::cout << "2.Student" << std::endl;
	std::cout << "3.Przedmiot" << std::endl;
	std::cout << "4.Powrot" << std::endl;
	std::cout << "Wybierz opcje: " << std::endl;
}

void Menu::show_add_result(std::string result)
{
	std::cout << "Status: " << result << std::endl;
	std::cout << "1.Menu glowne" << std::endl;
	std::cout << "Wybierz opcje: " << std::endl;
}

void Menu::show_details(Database* database, unsigned int option, unsigned int id)
{
	if (option == 1)
	{
		auto lecturer = database->get_lecturer_by_id(id);
		std::cout << "ID: " << lecturer.id_ << std::endl;
		std::cout << "Imie: " << lecturer.first_name_ << std::endl;
		std::cout << "Nazwisko: " << lecturer.last_name_ << std::endl;
		std::cout << "Prowadzone przedmioty: " << std::endl;
		for (auto id_subject : lecturer.id_subjects_)
		{
			auto subject = database->get_subject_by_id(id_subject);
			std::cout << "\t" << "ID: " << subject.id_ << std::endl;
			std::cout << "\t  " << "Nazwa: " << subject.name_ << std::endl;
			std::cout << "\t  " << "Zapisanych studentow: " << subject.id_students_.size() << std::endl;
		}
		std::cout << std::endl;
		std::cout << "1.Edytuj imie (not implemented)" << std::endl;
		std::cout << "2.Edytuj nazwisko (not implemented)" << std::endl;
		//std::cout << "3.Dodaj przedmiot" << std::endl;
		//std::cout << "4.Usun przedmiot" << std::endl;
		std::cout << "5.Usun prowadzacego" << std::endl;
		std::cout << "6.Powrot" << std::endl;
		std::cout << "Wybierz opcje: " << std::endl;
	}
	if (option == 2)
	{
		auto student = database->get_student_by_id(id);
		std::cout << "ID: " << student.id_ << std::endl;
		std::cout << "Imie: " << student.first_name_ << std::endl;
		std::cout << "Nazwisko: " << student.last_name_ << std::endl;
		std::cout << "Zapisany na przedmioty: " << std::endl;
		for (auto id_subject : student.id_subjects_)
		{
			auto subject = database->get_subject_by_id(id_subject);
			
			std::cout << "\t" << "ID: " << subject.id_ << std::endl;
			std::cout << "\t  " << "Nazwa: " << subject.name_ << std::endl;
			std::cout << "\t  " << "Oceny studenta: ";
			for(auto& grade : subject.id_grades_)
			{
				if(grade.first == student.id_)
				{
					std::cout << static_cast<int>(grade.second) << " ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "1.Edytuj imie" << std::endl;
		std::cout << "2.Edytuj nazwisko" << std::endl;
		std::cout << "3.Dodaj przedmiot" << std::endl;
		std::cout << "4.Usun przedmiot" << std::endl;
		std::cout << "5.Usun studenta" << std::endl;
		std::cout << "6.Powrot" << std::endl;
		std::cout << "Wybierz opcje: " << std::endl;
	}
	if (option == 3)
	{
		auto subject = database->get_subject_by_id(id);
		std::cout << "ID: " << subject.id_ << std::endl;
		std::cout << "Nazwa: " << subject.name_ << std::endl;
		std::cout << "Opis: " << subject.desc_ << std::endl;
		auto lecturer = database->get_lecturer_by_id(subject.id_lecturer_);
		std::cout << "Prowadzacy: " << lecturer.first_name_<< " "<< lecturer.last_name_ << std::endl;
		std::cout << "Zapisani studenci: " << std::endl;
		for (auto id_student : subject.id_students_)
		{
			auto student = database->get_student_by_id(id_student);
			std::cout << "\t" << "ID: " << student.id_ << std::endl;
			std::cout << "\t  " << "Imie: " << student.first_name_ << std::endl;
			std::cout << "\t  " << "Nazwisko: " << student.last_name_ << std::endl;
			std::cout << "\t  " << "Oceny studenta: ";
			for (auto& grade : subject.id_grades_)
			{
				if (grade.first == student.id_)
				{
					std::cout << static_cast<int>(grade.second) << " ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "1.Edytuj nazwe" << std::endl;
		std::cout << "2.Edytuj opis" << std::endl;
		std::cout << "3.Dodaj ocene" << std::endl;
		std::cout << "4.Usun ocene" << std::endl;
		std::cout << "5.Zmien prowadzacego" << std::endl;
		std::cout << "6.Usun przedmiot" << std::endl;
		std::cout << "7.Powrot" << std::endl;
		std::cout << "Wybierz opcje: " << std::endl;
	}
}
