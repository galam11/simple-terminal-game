#include "Player.h"
#include "Controller.h"
#include <iostream>
#include "conio.h"
#include "io.h"

Player::Player(const Location& location)
	: m_location(location) { }

void Player::setLocation(const Location& location)
{
	m_location = location;
}

const Location& Player::getLocation() const
{
	return m_location;
}

void Player::reduceLives()
{
	m_lives--;
}

const int Player::getLives() const
{
	return m_lives;
}

void Player::updateScore(bool isCoin, const int level)
{
	m_score = ((isCoin) ? 2 : 50) * level;
}

void Player::resetCoins()
{
	m_coins = 0;
}

void Player::coinCollected(const int level)
{
	m_coins++;
	updateScore(true, level);
}

void Player::move(Controller& controller)
{
	while (true) {

		Location nextLocation;
		
		int input = _getch();

		if (input == SpecialKeys::RIGHT && canMoveRightLeft())
			nextLocation = m_location.right();

		else if (input == SpecialKeys::LEFT && canMoveRightLeft())
			nextLocation = m_location.left();

		else if (input == SpecialKeys::UP && canMoveUpDown())
			nextLocation = m_location.up();

		else if (input == SpecialKeys::DOWN && canMoveUpDown())
			nextLocation = m_location.down();
		

		if (controller.movableLocation(nextLocation))
		{ 
			controller.drawDefaultCell(m_location);
			controller.drawCellAtLocation(PLAYER, nextLocation);

			setLocation(nextLocation);
			break;
		}
		
	}
}

bool Player::canMoveRightLeft()
{
	return true;
}

bool Player::canMoveUpDown()
{
	return true;
}



bool Player::enemyCollisionCheck(Controller& controller)
{
	for (int i = 0; i < controller.getNumberOfEnemies(); i++)
	{
		if (getLocation() == controller.getEnemyLocation(i))
		{
			reduceLives();
			return true;
		}
	}
	return false;
}