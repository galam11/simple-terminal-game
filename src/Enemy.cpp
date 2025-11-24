
#include "Enemy.h"
#include "Controller.h"
#include <iostream>


Enemy::Enemy(const Location& location)
	: m_location(location) { }

void Enemy::move(Controller& controller)
{
	auto nextLocation = m_moveRight ? m_location.right() : m_location.left();

	if (controller.movableLocation(nextLocation))
	{
		setLocation(nextLocation);
	}
	else
	{
		m_moveRight = !m_moveRight;
	}
}

void Enemy::draw(Controller& controller)
{
	controller.drawCellAtLocation(ENEMY, m_location);
}

void Enemy::setLocation(const Location& location)
{
	m_location = location;
}

const Location& Enemy::getLocation() const
{
	return m_location;
}
