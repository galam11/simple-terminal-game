#pragma once
#include "Board.h"
#include "Location.h"
#include <vector>

class Controller
{
private:
	Board m_board;
	bool m_running = true;

	// todo player
	//Player m_player
	// 
	// todo enemis
	//std::vector<Enemy> m_enemyList;

	void resetGame();
	void nextGame();
	void setDefualtEntitisLocations();
public:
	int getWidth() const;
	int getHeight() const;

	void run();
	void endGame();

	const Location& getPlayerLocation();
	const Location& getEnemyLocation(int i);

	char getCellAtLocation(const Location& location);

	bool walkbleLocation(const Location& location);
};