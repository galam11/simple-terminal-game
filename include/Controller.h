#pragma once
#include "Board.h"
#include "Location.h"
class Controller
{
private:
	Board m_board;
	bool m_running = false;
	// todo player

	// todo enemis

	void resetGame();
	void nextGame();
	void resetEntitisLocations();
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