#include "Controller.h"
#include "macros.h"
#include "conio.h"
#include "io.h"
#include <iostream>
#include "Location.h"
#include "Player.h"

void Controller::resetGame()
{
	Screen::resetLocation();
	m_board.draw();
	setEntitysStartingLocation();
}

void Controller::nextGame()
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
		//Location enemy_location = m_board.getEnemyStartLocation(i);
		//m_enemyList.push_back(Enemy(enemy_location));
		//drawCellAtLocation(ENEMY, enemy_location);
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
			m_enemyList[i].move(*this);
		}


		// temp fpr debuging
		switch (_getch())
		{
		case Keys::ESCAPE:
			nextGame();
			//m_running = false;
			break;

		case Keys::SPECIAL_KEY: //is this supposed to be spacebar?

			break;

		case SpecialKeys::RIGHT:
			m_player.move(*this, m_player.getLocation().right());
			break;

		case SpecialKeys::LEFT:
			m_player.move(*this, m_player.getLocation().left());
			break;

		case SpecialKeys::UP:
			m_player.move(*this, m_player.getLocation().up());
			break;

		case SpecialKeys::DOWN:
			m_player.move(*this, m_player.getLocation().down());
			break;

		default:
			break;
		}


	}
}

void Controller::endGame()
{
	if (m_player.getLives() == 0)
	{
		resetGame();
	}
	else
	{
		nextGame();
	}
}

void Controller::drawCellAtLocation(char cell, const Location& location)
{
	Screen::setLocation(location);
	std::cout << (char)cell;
}

void Controller::drawDefaultCell(const Location& location)
{
	drawCellAtLocation((char)getCellAtLocation(location), location);
}

const Location& Controller::getPlayerLocation() const //what for?
{
	// TODO: return player location
	return Location();
}

const Location& Controller::getEnemyLocation(int i) const //what for?
{
	return m_enemyList[i].getLocation();
}

char Controller::getCellAtLocation(const Location& location) const
{
	return (char) m_board.getAt(location);
}

bool Controller::movableLocation(const Location& location) const
{
	if (!m_board.LocationInBoard(location))
		return false;

	auto mid = m_board.getAt(location);

	if (mid == LADDER || mid == RAIL)
		return true;

	if (mid == FLOOR)
		return false;
	

	auto belowLocation = location.down();
	if (m_board.LocationInBoard(belowLocation))
	{
		char down = getCellAtLocation(location.down());

		if (down == FLOOR) //Player cant go ontop of ladder by rules
			return true;
	}

	return false;
}
