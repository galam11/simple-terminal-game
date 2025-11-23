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
	int m_width = 0, m_levelHeight = 0;
	std::vector<std::string> m_BoardData;
	int m_coinsInLevel;

	// Board class has the default locaition of enemies and the player
	std::vector<Location> m_enemiesStartLocations;
	Location m_playerStartLocation = Location(0,0);
	
	std::ifstream m_inputStream;

	void saveEntityState();

public:
	Board();
	~Board();

	bool loadNext();
	void draw() const;

	bool LocationInBoard(const Location& location) const;

	char getAt(const Location& location) const;
	int getWidth() const;
	int getHeight() const;
	int getLevel() const;
	int getCoinsInLevel() const;

	const Location& getPlayerStartLocation() const;
	const Location& getEnemyStartLocation(int i) const;
	int getEnemiesCount() const;
};