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
		switch (_getch())
		{
		case SpecialKeys::RIGHT:
			if (!controller.canMoveRightLeft(m_location, true))
				continue;
			nextLocation = m_location.right();
			break;

		case SpecialKeys::LEFT:
			if (!controller.canMoveRightLeft(m_location, false))
				continue;
			nextLocation = m_location.left();
			break;

		case SpecialKeys::UP:
			if (!controller.canMoveUpDown(m_location, true))
				continue;
			nextLocation = m_location.up();
			break;

		case SpecialKeys::DOWN:
			if (!controller.canMoveRightLeft(m_location, false))
				continue;
			nextLocation = m_location.down();
			break;

		default:
			continue;
		}

		
		controller.drawDefaultCell(m_location);
		controller.drawCellAtLocation(PLAYER, nextLocation);

		setLocation(nextLocation);
		break;
		
	}
}

//void Player::enemyCollision(Controller& controller)
//{
//
//}
//
//bool Player::enemyCollisionCheck(Controller& controller)
//{
//	for (int)
//	if (getLocation() == controller.getEnemyLocation())
//}