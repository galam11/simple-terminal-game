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

bool Player::coinCollsionCheck(Controller& controller)
{
	if (controller.getCellAtLocation(getLocation()) == COIN)
	{
		m_coins++;
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

		

		//if (controller.movableLocation(nextLocation))
		//{ 
		controller.drawDefaultCell(m_location);
		controller.drawCellAtLocation(PLAYER, nextLocation);

		setLocation(nextLocation);
		break;
		//}
	}
}

bool Player::canMoveRightLeft(Controller& controller, const Location& location)
{
	if (!controller.validLocationInBoard(location))
		return false;

	auto belowLocation = location.down();
	if (controller.validLocationInBoard(belowLocation))
	{
		auto down = controller.getCellAtLocation(belowLocation);
		if ((down == FLOOR || down == LADDER) && controller.getCellAtLocation(location) != FLOOR)
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
			reduceLives();
			return true;
		}
	}
	return false;
}