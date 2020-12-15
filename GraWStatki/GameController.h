#pragma once
#include <iostream>
#include <ostream>


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
		players[0] = new Human();
		players[1] = new AI();
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
		case game_state::PLAYING:
			players[0]->show_map();
			break;
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
		case 1: 
			for (auto& a : players)
				a->place_ship_randomly();
			state = game_state::PLAYING;
			break;
		case 2: break;
		case 3: game_flag = false; break;
		default: ;
		}
		
	}	
};

