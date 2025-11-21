
#include "Enemy.h"
#include "Controller.h"
#include <iostream>


Enemy::Enemy(const Location& location)
	: m_location(location) { }

void Enemy::update(Controller& controller)
{
	auto nextLocation = m_moveRigth ? m_location.right() : m_location.left();

	if (controller.walkbleLocation(nextLocation))
	{

		controller.drawDefualtCell(m_location);
		controller.drawCellAtLocation(ENEMY, nextLocation);
		
		setLocation(nextLocation);
	}
	else
	{
		m_moveRigth = !m_moveRigth;
	}
}

void Enemy::setLocation(const Location& location)
{
	m_location = location;
}

const Location& Enemy::getLocation() const
{
	return m_location;
}
