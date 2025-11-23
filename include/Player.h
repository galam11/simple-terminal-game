#pragma once

#include "Location.h"
#include "macros.h"

class Controller;

class Player
{
public:

	Player() = default;
	Player(const Location& location);

	void move(Controller& controller);
	void setLocation(const Location& location);
	const Location& getLocation() const;

	const int getLives() const;

	void updateScore(bool isCoin, const int level);

	void resetCoins();
	//const int getCoins() const;
	//bool enemyCollisionCheck(Controller& controller);

private:

	//void enemyCollision(Controller& controller);
	void reduceLives();
	void coinCollected(const int level);
	Location m_location = Location(0, 0);
	int m_lives = LIVES;
	int m_coins = 0;
	int m_score = 0;
};
