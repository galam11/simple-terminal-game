#include "Controller.h"
#include "macros.h"

void Controller::resetGame()
{

}

void Controller::nextGame()
{

}

void Controller::resetEntitisLocations()
{

}

int Controller::getWidth() const
{
	return m_board.getWidth();
}

int Controller::getHeight() const
{
	return m_board.getHight();
}

void Controller::run()
{

}

void Controller::endGame()
{

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
	char mid = getCellAtLocation(location);
	char down = getCellAtLocation(location.down());
	

	if (mid == LEDDER || mid == RAIL)
		return true;

	if (down == LEDDER || down == FLORE)
		return true;

	return false;
}
