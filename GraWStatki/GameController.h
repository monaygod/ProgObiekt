#pragma once
#include <iostream>
#include <ostream>
#include <fstream>


#include "AI.h"
#include "Board.h"
#include "Human.h"
#include "Player.h"

class GameController
{
	std::string player_name;
	game_state state;
	bool game_flag = true;
	std::vector<Player*> players;

	
public:

	GameController(): state(game_state::INITIALIZING), players(2)
	{
		initialize();
	}

	~GameController() = default;

	void main_loop()
	{
		std::string comm;
		while(game_flag)
		{
			system("cls");
			dispatch();
			std::cin >> comm;
			dispatch(comm);
		}
	}


	void dispatch()
	{
		switch(state)
		{
		case game_state::MAIN_MENU: main_menu_show(); break;
		case game_state::PREPARING_TO_GAME: break;
		case game_state::PLAYING: game_show(); break;
		case game_state::INITIALIZING: break;
		default: state = game_state::MAIN_MENU;
		}
	}

	void dispatch(std::string command)
	{
		switch (state)
		{
		case game_state::MAIN_MENU: main_menu_dispatch(command); break;
		case game_state::PREPARING_TO_GAME: break;
		case game_state::PLAYING:game_dispatch(command); break;
		case game_state::INITIALIZING: break;
		default: state = game_state::MAIN_MENU;
		}
	}

	void initialize()
	{
		if (players[0]) delete players[0];
		players[0] = new Human();
		if (players[1]) delete players[1];
		players[1] = new AI();
	}

	void save_game()
	{
		std::fstream plik;
		try {
			plik.open("save", std::ios::out | std::ios::binary);;
			plik.write((char*)this, sizeof(GameController));
			//plik.write((char*)players[0], sizeof(Player));
			plik.close();
		}
		catch(std::exception e)
		{
			std::cout << e.what();
		}
	}

	void load_game()
	{
		std::fstream plik;
		try {
			plik.open("save", std::ios::in | std::ios::binary);;
			plik.read((char*)this, sizeof(GameController));
			plik.close();
		}
		catch (std::exception e)
		{
			std::cout << e.what();
			std::system("pause");
		}
	}
	
	void start()
	{
		std::cout << "Podaj nazwe gracza: " << std::endl;
		std::cin >> player_name;
		state = game_state::MAIN_MENU;
		main_loop();
	}

#pragma region show
	
	void main_menu_show()
	{
		std::cout << "\tGRA W STATKI" << std::endl;
		std::cout << "1. Rozpocznij gre z losowym rozmieszczeniem statkow" << std::endl;
		std::cout << "2. Wczytaj gre" << std::endl;
		std::cout << "3. Wyjscie" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Opcja: ";
	}

	void game_show()
	{
		std::cout << std::right << std::setw(15) << std::setfill(' ') << "Statki" << '\t';
		std::cout << std::right << std::setw(24) << std::setfill(' ') << "Strzaly";
		std::cout << std::endl;
		players[0]->show_map();
		players[1]->show_map();
		std::cout << std::endl << "(np 4a lub a4)(wpisz exit zeby wyjsc do menu glownego) ";
		std::cout << std::endl << "Wybierz cel do strzalu: ";

	}

#pragma endregion show

#pragma region dispatch
	void main_menu_dispatch(std::string command)
	{
		int a = std::stoi(command);
		switch(a)
		{
		case 1: 
			for (auto& a : players)
				a->place_ship_randomly();
			state = game_state::PLAYING;
			break;
		case 2: 
			load_game();
			state = game_state::PLAYING;
			break;
		case 3: game_flag = false; break;
		default: ;
		}
		
	}

	void game_dispatch(std::string command)
	{
		if (command.length() != 2) {
			if (command == "exit") {
				initialize();
				state = game_state::MAIN_MENU;
			}
			if (command == "save") {
				save_game();
				state = game_state::MAIN_MENU;
			}
			return;
		}
		int x, y;
		char temp;
		if (isdigit(command[0]) && isalpha(command[1]))
		{
			x = atoi(&command[0]);
			temp = command[1];
		}
		else if (isdigit(command[1]) && isalpha(command[0]))
		{
			x = atoi(&command[1]);
			temp = command[0];
		}
		else return;
		temp = tolower(temp);
		y = temp - 'a';
		players[0]->fire(x, y, players[1]);
		players[1]->fire(x, y, players[0]);		
	}

#pragma endregion dispatch
};

