#include "Controller.h"
#include "macros.h"
#include "conio.h"
#include "io.h"
#include <iostream>
#include "Location.h"
#include "Player.h"

void Controller::resetLevel()
{
	Screen::resetLocation();
	m_board.draw();
	setEntitysStartingLocation();
}

int Controller::getNumberOfEnemies()
{
	return m_enemyList.size();
}

void Controller::nextLevel()
{
	if ((m_running = m_board.loadNext()))
	{
		Screen::resetLocation();
		system("cls");
		m_board.draw();

		m_enemyList.resize(m_board.getEnemiesCount());

		setEntitysStartingLocation();
	}
	else
	{
		Screen::resetLocation();
		system("cls");
	}
}

void Controller::setEntitysStartingLocation()
{
	Location player_location = m_board.getPlayerStartLocation();
	m_player.setLocation(player_location);
	drawCellAtLocation(PLAYER, player_location);

	
	for (int i = 0; i <m_enemyList.size(); i++)
	{
		m_enemyList[i].setLocation(m_board.getEnemyStartLocation(i));
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

char Controller::getCellAtLocation(const Location& location)
{
	return m_board.getAt(location);
}

bool Controller::validLocationInBoard(const Location& location) const
{
	return m_board.LocationInBounds(location);
}

int Controller::getLevel() const
{
	return m_board.getLevel();
}

void Controller::run()
{
	nextLevel();

	while (m_running)
	{
		m_player.move(*this);

		if (m_player.coinCollsionCheck(*this))
			m_board.removeCoin(m_player.getLocation());

		if (m_player.enemyCollisionCheck(*this))
			resetLevel();

		for (int i = 0; i < m_enemyList.size(); i++)
			m_enemyList[i].move(*this);

		if (m_player.enemyCollisionCheck(*this))
			resetLevel();



	}
}

void Controller::levelSuccess()
{
	//
}

void Controller::drawCellAtLocation(char cell, const Location& location)
{
	Screen::setLocation(location);
	std::cout << (char)cell;
}

void Controller::drawDefaultCell(const Location& location)
{
	drawCellAtLocation((char)m_board.getAt(location), location);
}

const Location& Controller::getPlayerLocation() const //what for?
{
	// TODO: return player location
	return Location();
}

const Location& Controller::getEnemyLocation(int i) const
{
	return m_enemyList[i].getLocation();
}

bool Controller::movableLocation(const Location& location) const
{
	if (!m_board.LocationInBounds(location))
		return false;

	auto mid = m_board.getAt(location);

	if (mid == LADDER || mid == RAIL)
		return true;

	if (mid == FLOOR)
		return false;
	

	auto belowLocation = location.down();
	if (m_board.LocationInBounds(belowLocation))
	{
		char down = m_board.getAt(belowLocation);

		if (down == FLOOR)
			return true;
	}

	return false;
}
