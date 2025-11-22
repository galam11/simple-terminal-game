#pragma once

#include "Location.h"
#include "macros.h"

class Controller;

class Player
{
public:

	Player() = default;
	Player(const Location& location);

	void move(Controller& controller, const Location& nextLocation);
	void setLocation(const Location& location);
	const Location& getLocation() const;

	void reduceLives();
	const int getLives() const;

	void updateScore(bool isCoin, int level);

	void resetCoins();
	void coinCollected();
	//const int getCoins() const;

private:

	Location m_location = Location(0, 0);
	int m_lives = LIVES;
	int m_coins = 0;
	int m_score = 0;
};
