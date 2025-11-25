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

void Controller::loadNextLevel()
{
	m_player.updateScore(false, getLevel());
	if ((m_running = m_board.loadNext()))
	{
		Screen::resetLocation();
		system("cls");

		m_enemyList.resize(m_board.getEnemiesCount());

		setEntitysStartingLocation();

		m_player.resetCoins();
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
	for (int i = 0; i < m_enemyList.size(); i++)
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
	loadNextLevel();

	drawGame();

	while (m_running)
	{
		updateGame();

		drawGame();
	}

	gameOverScreen(true);
}

void Controller::updateGame()
{
	if (!m_player.update(*this))
		handlePlayerHit();

	for (int i = 0; i < m_enemyList.size(); i++)
		m_enemyList[i].move(*this);

	if (m_board.getCoinsInLevel() == m_player.getCoins())
		loadNextLevel();
}

void Controller::drawGame()
{
	Screen::resetLocation();

	m_board.draw();

	m_player.draw(*this);

	for (int i = 0; i < m_enemyList.size(); i++)
		m_enemyList[i].draw(*this);

	Screen::setLocation(Location(m_board.getHeight(), 0));
	std::cout << "Lives: " << m_player.getLives() << "  Level: " << getLevel() << "  Score: " << m_player.getScore() << std::endl;
}

void Controller::handlePlayerHit()
{
	if (m_player.getLives() == 0)
	{
		gameOverScreen(false);
		exit(EXIT_SUCCESS);
	}
	else
	{
		resetLevel();
	}
}

void Controller::gameOverScreen(bool win)
{
	Screen::resetLocation();
	system("cls");
	std::cout << "Game Over! ," << (win ? "You Won!" : "You Lost!")
		<< '\n' << '\t' << " score: " << m_player.getScore() << std::endl;
}

void Controller::drawCellAtLocation(char cell, const Location& location)
{
	Screen::setLocation(location);
	std::cout << (char)cell;
}

const Location& Controller::getPlayerLocation() const
{
	return m_player.getLocation();
}

const Location& Controller::getEnemyLocation(int i) const
{
	return m_enemyList[i].getLocation();
}

bool Controller::removeCoin(const Location& location)
{
	return m_board.removeCoin(location);
}