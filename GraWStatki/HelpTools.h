#pragma once

const int ship_table[5] = { 2,3,3,4,5 };
const int ship_number = 5;


enum class game_state
{
	INITIALIZING,
	MAIN_MENU,
	PREPARING_TO_GAME,
	PLAYING
};