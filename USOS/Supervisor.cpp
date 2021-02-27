#pragma once
#include "Supervisor.h"

void Supervisor::start()
{
	state_ = State::MAIN_MENU;
	loop();
}

void Supervisor::loop()
{
	while (program_stop_flag)
	{
		system("cls");
		display();
		std::cin >> buffer;
		dispatch();
	}
}

void Supervisor::display()
{
	switch (state_)
	{
	case State::MAIN_MENU: Menu::show_main_menu();
		break;
	case State::ADD_MENU: Menu::show_choose_element();
		break;
	case State::ADD_DETAILS: Menu::show_add_result(buffer);
		break;
	case State::SHOW_MENU: Menu::show_choose_element();
		break;
	case State::SHOW_DETAILS: Menu::show_details(&main_database_, temp_int_2, temp_int_1);
		break;
	default:;
	}
}

void Supervisor::dispatch()
{
	switch (state_)
	{
	case State::MAIN_MENU: dispatch_main_menu();
		break;
	case State::ADD_MENU: dispatch_add_menu();
		break;
	case State::ADD_DETAILS: dispatch_add_details();
		break;
	case State::SHOW_MENU: dispatch_show_menu();
		break;
	case State::SHOW_DETAILS: dispatch_show_details();
		break;
	default: state_ = State::MAIN_MENU;;
	}
}

void Supervisor::dispatch_main_menu()
{
	if (buffer == "1")
	{
		state_ = State::SHOW_MENU;
		return;
	}
	if (buffer == "2")
	{
		state_ = State::ADD_MENU;
		return;
	}
	if (buffer == "3")
	{
		//TODO zapis
		save_data();
		return;
	}
	if (buffer == "4")
	{
		//TODO wczytaj
		load_data();
		return;
	}
	if (buffer == "5")
	{
		program_stop_flag = false;
		return;
	}
	return;
}

void Supervisor::dispatch_add_menu()
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
		std::string nazwa, opis;
		unsigned int id_lecturer;
		std::cout << "Dodaj Przedmiot" << std::endl;
		std::cout << "Nazwa: ";
		std::cin >> nazwa;
		std::cout << "Opis: ";
		std::cin >> opis;
		std::cout << "ID prowadzacego: ";
		std::cin >> id_lecturer;
		if (main_database_.add_subject(id_lecturer, nazwa, opis)) {
			buffer = "Sukces";
			Lecturer& nowy_wykladowca = main_database_.get_lecturer_by_id(id_lecturer);
			nowy_wykladowca.id_subjects_.push_back(main_database_.subjects_id_counter);
		}
		else
			buffer = "Blad";
		state_ = State::ADD_DETAILS;
	}
	if (buffer == "4")
	{
		state_ = State::MAIN_MENU;
	}
}

void Supervisor::dispatch_add_details()
{
	state_ = State::MAIN_MENU;
}

void Supervisor::dispatch_show_menu()
{
	if (buffer == "1" || buffer == "2" || buffer == "3")
	{
		unsigned int id;
		system("cls");
		std::cout << "Podaj ID: ";
		std::cin >> id;
		temp_int_1 = id;
		temp_int_2 = std::stoi(buffer.substr(0, 1));
		state_ = State::SHOW_DETAILS;
	}
	if (buffer == "4")
	{
		state_ = State::MAIN_MENU;
	}
}

void Supervisor::dispatch_show_details()
{
	if (temp_int_2 == 1) {
		Lecturer& rekord_do_edycji = main_database_.get_lecturer_by_id(temp_int_1);		
		if (buffer == "1")
		{
			std::string imie;
			std::cout << "Podaj nowe imie:";
			std::cin >> imie;
			rekord_do_edycji.first_name_ = imie;
		}
		if (buffer == "2")
		{
			std::string nazwisko;
			std::cout << "Podaj nowe nazwisko:";
			std::cin >> nazwisko;
			rekord_do_edycji.last_name_ = nazwisko;
		}
		if(buffer == "3")
		{
			unsigned int id;
			std::cout << "Podaj id przedmiotu:";
			std::cin >> id;
			rekord_do_edycji.id_subjects_.push_back(id);
		}
		if (buffer == "4")
		{
			unsigned int id;
			std::cout << "Podaj id przedmiotu:";
			std::cin >> id;
			rekord_do_edycji.id_subjects_.erase(std::remove_if(
				rekord_do_edycji.id_subjects_.begin(), rekord_do_edycji.id_subjects_.end(),
				[id](const unsigned int& x)
			{
				return x == id;
			}), rekord_do_edycji.id_subjects_.end());
		}
		if (buffer == "5")
		{
			main_database_.remove_lecturer(temp_int_1);
			state_ = State::SHOW_MENU;
		}
		if(buffer == "6")
		{
			state_ = State::SHOW_MENU;
		}
	}
	if (temp_int_2 == 2) {
		Student& rekord_do_edycji = main_database_.get_student_by_id(temp_int_1);
		if (buffer == "1")
		{
			std::string imie;
			std::cout << "Podaj nowe imie:";
			std::cin >> imie;
			rekord_do_edycji.first_name_ = imie;
		}
		if (buffer == "2")
		{
			std::string nazwisko;
			std::cout << "Podaj nowe nazwisko:";
			std::cin >> nazwisko;
			rekord_do_edycji.last_name_ = nazwisko;
		}
		if (buffer == "3")
		{
			unsigned int id;
			std::cout << "Podaj id przedmiotu:";
			std::cin >> id;
			Subject& przedmiot = main_database_.get_subject_by_id(id);
			rekord_do_edycji.id_subjects_.push_back(id);
			przedmiot.id_students_.push_back(temp_int_1);
		}
		if (buffer == "4")
		{
			unsigned int id;
			std::cout << "Podaj id przedmiotu:";
			std::cin >> id;
			Subject& przedmiot = main_database_.get_subject_by_id(id);
			rekord_do_edycji.id_subjects_.erase(std::remove_if(
				rekord_do_edycji.id_subjects_.begin(), rekord_do_edycji.id_subjects_.end(),
				[id](const unsigned int& x)
			{
				return x == id;
			}), rekord_do_edycji.id_subjects_.end());
			przedmiot.id_students_.erase(std::remove_if(
				przedmiot.id_students_.begin(), przedmiot.id_students_.end(),
				[id](const unsigned int& x)
			{
				return x == id;
			}), przedmiot.id_students_.end());
		}
		if (buffer == "5")
		{
			main_database_.remove_student(temp_int_1);
			state_ = State::SHOW_MENU;
		}
		if (buffer == "6")
		{
			state_ = State::SHOW_MENU;
		}
	}
	if (temp_int_2 == 3) {
		Subject& rekord_do_edycji = main_database_.get_subject_by_id(temp_int_1);
		if (buffer == "1")
		{
			std::string nazwa;
			std::cout << "Podaj nowa nazwe:";
			std::cin >> nazwa;
			rekord_do_edycji.name_ = nazwa;
		}
		if (buffer == "2")
		{
			std::string opis;
			std::cout << "Podaj nowe nazwisko:";
			std::cin >> opis;
			rekord_do_edycji.desc_ = opis;
		}
		if (buffer == "3")
		{
			unsigned int id_stud, ocena;
			std::cout << "Podaj id studenta:";
			std::cin >> id_stud;
			std::cout << "Podaj ocene (2-5):";
			std::cin >> ocena;
			if (ocena < 2 || ocena > 5)
				return;
			rekord_do_edycji.add_grade(id_stud, static_cast<Grade>(ocena));
		}
		if (buffer == "4")
		{
			unsigned int id_stud, ocena;
			std::cout << "Podaj id studenta:";
			std::cin >> id_stud;
			std::cout << "Podaj ocene (2-5):";
			std::cin >> ocena;
			rekord_do_edycji.id_grades_.erase(std::remove_if(
				rekord_do_edycji.id_grades_.begin(), rekord_do_edycji.id_grades_.end(),
				[id_stud, ocena](const std::pair<unsigned int, Grade>& x)
			{
				return (x.first == id_stud && x.second == static_cast<Grade>(ocena));
			}), rekord_do_edycji.id_grades_.end());
		}
		if (buffer == "5")
		{
			unsigned int id;
			std::cout << "Podaj id wykladowcy:";
			std::cin >> id;
			Lecturer& nowy_wykladowca = main_database_.get_lecturer_by_id(id);
			Lecturer& stary_wykladowca = main_database_.get_lecturer_by_id(rekord_do_edycji.id_lecturer_);
			rekord_do_edycji.id_lecturer_ = id;
			nowy_wykladowca.id_subjects_.push_back(temp_int_1);
			stary_wykladowca.id_subjects_.erase(std::remove_if(
				stary_wykladowca.id_subjects_.begin(), stary_wykladowca.id_subjects_.end(),
				[id](const unsigned int& x)
			{
				return x == id;
			}), stary_wykladowca.id_subjects_.end());
		}
		if (buffer == "6")
		{
			main_database_.remove_subject(temp_int_1);
			state_ = State::SHOW_MENU;
		}
		if (buffer == "7")
		{
			state_ = State::SHOW_MENU;
		}
	}
}

void Supervisor::save_data()
{
	std::fstream plik;
	try
	{
		plik.open("save", std::ios::out | std::ios::binary);
		plik.write((char*)&main_database_, sizeof(main_database_));
		plik.close();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

void Supervisor::load_data()
{
	std::fstream plik;
	try
	{
		plik.open("save", std::ios::in | std::ios::binary);;
		plik.read((char*)&main_database_, sizeof(Database));
		plik.close();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		std::system("pause");
	}
}