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

const int Player::getLives() const
{
	return m_lives;
}

void Player::updateScore(bool isCoin, const int level)
{
	m_score += ((isCoin) ? COIN_SCORE : LEVEL_UP_SCORE) * level;
}

int Player::getScore()
{
	return m_score;
}

const int Player::getCoins() const
{
	return m_coins;
}

void Player::resetCoins()
{
	m_coins = 0;
}

bool Player::coinCollsionCheck(Controller& controller)
{
	if (controller.removeCoin(m_location))
	{
		m_coins += 1;
		updateScore(true, controller.getLevel());
		return true;
	}
	return false;
}

void Player::move(Controller& controller)
{
	while (true) {

		Location nextLocation = Location(0, 0);
		
		int input = _getch();

		if (input == SpecialKeys::RIGHT)
		{
			nextLocation = m_location.right();
			if (!canMoveRightLeft(controller, nextLocation))
				continue;
		}
		else if (input == SpecialKeys::LEFT)
		{
			nextLocation = m_location.left();
			if (!canMoveRightLeft(controller, nextLocation))
				continue;
		}
		else if (input == SpecialKeys::DOWN)
		{
			nextLocation = m_location.down();
			if (!canMoveUpDown(controller, nextLocation))
				continue;
		}
		else if (input == SpecialKeys::UP)
		{
			nextLocation = m_location.up();
			if (!canMoveUpDown(controller, nextLocation))
				continue;
		}
		else continue;

		setLocation(nextLocation);

		break;
	}
}

bool Player::update(Controller& controller)
{
	if (enemyCollisionCheck(controller))
		return false;

	move(controller);

	coinCollsionCheck(controller);

	if (enemyCollisionCheck(controller))
		return false;
	return true;
}

void Player::draw(Controller& controller)
{
	controller.drawCellAtLocation(PLAYER, m_location);
}


bool Player::canMoveRightLeft(Controller& controller, const Location& location)
{
	if (!controller.validLocationInBoard(location))
		return false;

	auto belowLocation = location.down();
	if (controller.validLocationInBoard(belowLocation))
	{
		auto down = controller.getCellAtLocation(belowLocation);
		auto mid = controller.getCellAtLocation(location);

		if (( (down == FLOOR || down == LADDER) && mid != FLOOR ) || mid == LADDER)
			return true;
	}

	return controller.getCellAtLocation(location) == RAIL;
}

bool Player::canMoveUpDown(Controller& controller, const Location& location)
{
	return controller.validLocationInBoard(location) 
		&& controller.getCellAtLocation(location) == LADDER
		&& controller.getCellAtLocation(m_location) == LADDER;
}

bool Player::enemyCollisionCheck(Controller& controller)
{
	for (int i = 0; i < controller.getNumberOfEnemies(); i++)
	{
		if (getLocation() == controller.getEnemyLocation(i))
		{
			m_lives--;
			return true;
		}
	}
	return false;
}