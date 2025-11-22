#pragma once
#include <string>

const std::string FILE_PATH = "Board.txt";


enum Cells {
	ENEMY	= '%',
	PLAYER	= '@',
	COIN	= '*',
	LADDER	= 'H',
	RAIL	= '-',
	FLOOR	= '#',
	EMPTY	= ' '
};

const int LIVES = 3;