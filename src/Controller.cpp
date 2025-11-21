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
		//m_board.draw();
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
	return m_board.getHight();
}

void Controller::run()
{
	

	
	for (int i = 0; i < 20; i++)
	{
		Screen::setLocation(Location(0, i));
		std::cout << '#';
	}


	//nextGame();

	//while (m_running)
	//{

	//	// TODO : update enemis

	//	// TODO : update player

	//	for (int y = 0; y < m_board.getHight(); y++)
	//		for (int x = 0; x < m_board.getWidth(); x++)
	//		{
	//			Location loc (x, y);
	//			Screen::setLocation(loc);
	//			char c = getCellAtLocation(loc);
	//			std::cout << c;
	//			/*if (walkbleLocation(loc))
	//			{
	//				Screen::setLocation(loc);
	//				std::cout << '&';
	//			}*/
	//		}
	//	
	//	int t = _getch();
	//	system("cls");
	//	nextGame();
	//	
	//}
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
	if (location.col >= getWidth() || location.col < 0 || location.row >= getHeight() || location.row < 0)
		return false;


	char mid = getCellAtLocation(location);
	char down = getCellAtLocation(location.down());
	

	if (mid == LEDDER || mid == RAIL)
		return true;

	if (down == LEDDER || down == FLORE)
		return true;

	return false;
}
