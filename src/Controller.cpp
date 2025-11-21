#include "Controller.h"
#include "macros.h"
#include "conio.h"
#include "io.h"
#include <iostream>

void Controller::resetGame()
{
	setDefualtEntitisLocations();
}

void Controller::nextGame()
{
	if ((m_running = m_board.loadNext()))
	{
		Screen::resetLocation();
		m_board.draw();
		setDefualtEntitisLocations();
	}
}

void Controller::setDefualtEntitisLocations()
{

}

int Controller::getWidth() const
{
	return m_board.getWidth();
}

int Controller::getHeight() const
{
	return m_board.getHeight();
}

void Controller::run()
{
	while (m_running)
	{
		// todo update enemies

		// todo update player

		if (_getch() == Keys::ESCAPE)
			endGame();
	}
}

void Controller::endGame()
{
	//if (/*check if player health is zero*/)
	//{
	//	resetGame();
	//}
	//else 
	//{

		nextGame();

	//}
}

const Location& Controller::getPlayerLocation()
{
	// TODO: return player location
	return Location();
}

const Location& Controller::getEnemyLocation(int i)
{
	// TODO: return enemis location based on index
	return Location();
}

char Controller::getCellAtLocation(const Location& location)
{
	return m_board.getAt(location);
}

bool Controller::walkbleLocation(const Location& location)
{
	if (m_board.validLocation(location))
	{
		char mid = getCellAtLocation(location);

		if (mid == LEDDER || mid == RAIL)
			return true;

		if (mid == FLORE)
			return false;
	}

	auto downLoc = location.down();
	if (m_board.validLocation(downLoc))
	{
		char down = getCellAtLocation(location.down());

		if (down == LEDDER || down == FLORE)
			return true;
	}

	return false;
}
