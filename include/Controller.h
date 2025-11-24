#pragma once
#include "Board.h"
#include "Enemy.h"
#include <vector>
#include "Player.h"

class Location;

class Controller
{
private:
	Board m_board;
	bool m_running = true;

	Player m_player; 
	std::vector<Enemy> m_enemyList;

	void resetLevel();
	void loadNextLevel();
	void setEntitysStartingLocation();
	void drawGame();
	void updateGame();

	void gameOverScreen(bool win);

public:
	int getWidth() const;
	int getHeight() const;
	int getLevel() const;

	char getCellAtLocation(const Location& location);
	bool validLocationInBoard(const Location& location) const;
	bool removeCoin(const Location& location);
	void run();
	
	void drawCellAtLocation(char cell, const Location& location);
	void drawDefaultCell(const Location& location);

	const Location& getPlayerLocation() const;
	const Location& getEnemyLocation(int i) const;

	bool movableLocation(const Location& location) const;

	int getNumberOfEnemies();

	
	void handlePlayerHit();
};