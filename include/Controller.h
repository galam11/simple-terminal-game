#pragma once
#include "Board.h"
#include "Enemy.h"
#include <vector>
#include "Player.h"

class Location;

class Controller
{
public:
	Controller() = default;

	void run();

	int getWidth() const;
	int getHeight() const;
	int getLevel() const;
	int getNumberOfEnemies();
	char getCellAtLocation(const Location& location);
	const Location& getPlayerLocation() const;
	const Location& getEnemyLocation(int i) const;

	bool validLocationInBoard(const Location& location) const;
	bool removeCoin(const Location& location);
	bool movableLocation(const Location& location) const;

	void drawCellAtLocation(char cell, const Location& location);
	void drawDefaultCell(const Location& location);
	
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
	void handlePlayerHit();

};