#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <Location.h>


const std::string FILE_PATH = "Board.txt";

const char ENEMY = '%';
const char PLAYER = '@';
const char COIN = '*';
const char LEDDER = 'H';
const char RAIL = '-';
const char FLORE = '#';
const char EMPTY = ' ';

// Level class - can be renamed to Bored
class Level
{
private:
	int m_levelIndex = 0;
	int m_levelWidth = 0, m_levelHight = 0;
	std::vector<std::string> m_levelData;


	// Level class has the defualt locaition of enemies and the player
	std::vector<Location> m_enemiesStartLocations;
	Location m_playerStartLocation = Location(0,0);
	
	std::ifstream m_inputStreem;

	void saveEntitisState();

public:
	Level();
	~Level();

	void loadNext();
	void drawLevel() const;

	char getAt(const Location& location) const;
	int getLevelWidth() const;
	int getLevelHight() const;
	int getCurrentLevel() const;
};