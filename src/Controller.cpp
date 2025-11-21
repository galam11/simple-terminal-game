#include "Controller.h"
#include "macros.h"
#include "conio.h"
#include "io.h"
#include <iostream>
#include "Location.h"

void Controller::resetGame()
{
	Screen::resetLocation();
	m_board.draw();
	setDefualtEntitisLocations();
}

void Controller::nextGame()
{
	if ((m_running = m_board.loadNext()))
	{
		Screen::resetLocation();
		system("cls");
		m_board.draw();
		setDefualtEntitisLocations();
	}
	else
	{
		Screen::resetLocation();
		system("cls");
	}
}

void Controller::setDefualtEntitisLocations()
{
	// todo set player location

	m_enemyList.clear();
	for (int i = 0; i < m_board.getEnemiesCount(); i++)
	{
		m_enemyList.push_back(Enemy(m_board.getEnemyStartLocation(i)));
		drawCellAtLocation(ENEMY, m_board.getEnemyStartLocation(i));
	}
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
	nextGame();

	while (m_running)
	{
		// todo update enemies

		for (int i = 0; i < m_enemyList.size(); i++)
		{
			m_enemyList[i].update(*this);
		}

		switch (_getch())
		{
		case Keys::ESCAPE:
			m_running = false;
			break;

		case SpecialKeys::RIGHT:
			endGame();
			break;

		case SpecialKeys::LEFT:
			resetGame();
			break;

		default:
			break;
		}


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

void Controller::drawCellAtLocation(Cells cell, const Location& location)
{
	Screen::setLocation(location);
	std::cout << (char)cell;
}

void Controller::drawDefualtCell(const Location& location)
{
	Screen::setLocation(location);
	std::cout << m_board.getAt(location);
}

const Location& Controller::getPlayerLocation()
{
	// TODO: return player location
	return Location();
}

const Location& Controller::getEnemyLocation(int i)
{
	return m_enemyList[i].getLocation();
}

char Controller::getCellAtLocation(const Location& location) const
{
	return m_board.getAt(location);
}

bool Controller::walkbleLocation(const Location& location) const
{
	if (!m_board.validLocation(location))
		return false;

	char mid = getCellAtLocation(location);

	if (mid == LEDDER || mid == RAIL)
		return true;

	if (mid == FLORE)
		return false;
	

	auto downLoc = location.down();
	if (m_board.validLocation(downLoc))
	{
		char down = getCellAtLocation(location.down());

		if (down == LEDDER || down == FLORE)
			return true;
	}

	return false;
}
