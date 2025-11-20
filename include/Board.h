#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <Location.h>
#include "macros.h"



// Board class - can be renamed to Bored
class Board
{
private:
	int m_level = 0;
	int m_width = 0, m_levelHight = 0;
	std::vector<std::string> m_BoardData;


	// Board class has the defualt locaition of enemies and the player
	std::vector<Location> m_enemiesStartLocations;
	Location m_playerStartLocation = Location(0,0);
	
	std::ifstream m_inputStreem;

	void saveEntitisState();

public:
	Board();
	~Board();

	bool loadNext();
	void drawLevel() const;

	char getAt(const Location& location) const;
	int getWidth() const;
	int getHight() const;
	int getLevel() const;
};