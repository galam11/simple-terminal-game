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

		Location nextLocation;
		
		int input = _getch();

		if (input == SpecialKeys::RIGHT && canMoveRightLeft(controller))
			nextLocation = m_location.right();

		else if (input == SpecialKeys::LEFT && canMoveRightLeft(controller))
			nextLocation = m_location.left();

		else if (input == SpecialKeys::UP && canMoveUpDown(controller))
			nextLocation = m_location.up();

		else if (input == SpecialKeys::DOWN && canMoveUpDown(controller))
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

bool Player::canMoveRightLeft(Controller& controller)
{
	auto downloc = m_location.down();

	if (controller.validLocationInBoard(downloc))
	{
		auto cInLoc = controller.getCellAtLocation(m_location);
		auto cInDownLoc = controller.getCellAtLocation(downloc);

		if (cInDownLoc == FLOOR || cInLoc == RAIL)
			return true;
	}

	return false;
}

bool Player::canMoveUpDown(Controller& controller)
{
	return controller.getCellAtLocation(m_location) == LADDER;
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