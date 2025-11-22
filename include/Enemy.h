#pragma once

#include "Location.h"

class Controller;


class Enemy
{
private:
	Location m_location = Location(0, 0);
	bool m_moveRight = true;

	 
public:
	Enemy() = default;
	Enemy(const Location& location);

	void move(Controller& controller);
	void setLocation(const Location& location);
	const Location& getLocation() const;
};