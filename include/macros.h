#pragma once
#include <string>

const std::string FILE_PATH = "Board.txt";


enum Cells {
	ENEMY	= '%',
	PLAYER	= '@',
	COIN	= '*',
	LEDDER	= 'H',
	RAIL	= '-',
	FLORE	= '#',
	EMPTY	= ' '
};