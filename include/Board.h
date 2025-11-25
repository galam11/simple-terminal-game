#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <Location.h>
#include "macros.h"


class Board
{
public:
	Board();
	~Board();

	bool loadNext();
	void draw() const;

	char getAt(const Location& location) const;
	void SetAt(const Location& location, char val);

	int getWidth() const;
	int getHeight() const;
	int getLevel() const;
	int getCoinsInLevel() const;
	int getEnemiesCount() const;

	const Location& getPlayerStartLocation() const;
	const Location& getEnemyStartLocation(int i) const;

private:
	int m_level = 0;
	int m_width = 0, m_levelHeight = 0;
	std::vector<std::string> m_boardData;
	int m_coinsInLevel;

	// Board class has the default locaition of enemies and the player
	std::vector<Location> m_enemiesStartLocations;
	Location m_playerStartLocation = Location(0,0);
	
	std::ifstream m_inputStream;

	void saveEntityState();
};