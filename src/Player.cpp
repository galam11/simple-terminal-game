#include "Player.h"
#include "Controller.h"
#include <iostream>

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

void Player::updateScore(bool isCoin, int level)
{
	m_score = ((isCoin) ? 2 : 50) * level;
}

void Player::resetCoins()
{
	m_coins = 0;
}

void Player::coinCollected()
{
	m_coins++;
}

void Player::move(Controller& controller, const Location& nextLocation)
{
	if (controller.movableLocation(nextLocation))
	{
		controller.drawDefaultCell(m_location);
		controller.drawCellAtLocation(PLAYER, nextLocation);

		setLocation(nextLocation);
	}
}