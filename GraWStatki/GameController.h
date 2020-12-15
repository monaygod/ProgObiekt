#pragma once
#include <iostream>
#include <ostream>

#include "Board.h"

class GameController
{
	std::string player_name;
	game_state state;
	bool game_flag = true;
	std::vector<Board> game_boards;

	
public:

	GameController(): state(game_state::INITIALIZING)
	{
		game_boards.emplace_back();
		game_boards.emplace_back(true);
		game_boards.emplace_back();
		game_boards.emplace_back();
	}

	~GameController()
	{
		delete[] game_boards[0];
		delete[] game_boards[1];
		delete[] game_boards;
	}

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
		case game_state::PLAYING: break;
		case game_state::INITIALIZING: break;
		default: ;
		}
	}

	void dispatch(std::string command)
	{
		switch (state)
		{
		case game_state::MAIN_MENU: main_menu_dispatch(command); break;
		case game_state::PREPARING_TO_GAME: break;
		case game_state::PLAYING: break;
		case game_state::INITIALIZING: break;
		default:;
		}
	}
	
	void start()
	{
		std::cout << "Podaj nazwe gracza: " << std::endl;
		std::cin >> player_name;
		state = game_state::MAIN_MENU;
		main_loop();
	}
	
	void main_menu_show()
	{
		std::cout << "GRA W STATKI" << std::endl;
		std::cout << "1. Rozpocznij gre z losowym rozmieszczeniem statkow" << std::endl;
		std::cout << "2. Ustaw statki" << std::endl;
		std::cout << "3. Wyjscie" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Opcja: ";
	}

	void main_menu_dispatch(std::string command)
	{
		int a = std::stoi(command);
		switch(a)
		{
		case 1: break;
		case 2: break;
		case 3: game_flag = false; break;
		default: ;
		}
		
	}

	void plansze()
	{
		Board sasd;
		Board sasd2;

		auto a = sasd.print_to_console();
		auto b = sasd2.print_to_console();

		for (int i = 0; i < 10; i++)
		{
			std::cout << a[i] << "\t" << b[i] << std::endl;
		}
	}
	
};

