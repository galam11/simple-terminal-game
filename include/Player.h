#pragma once

#include "Location.h"
#include "macros.h"

class Controller;

class Player
{
public:
	Player() = default;
	Player(const Location& location);

	bool update(Controller& controller);
	void draw() const;
	
	void setLocation(const Location& location);
	
	const Location& getLocation() const;
	int getLives() const;
	int getCoins() const;
	int getScore() const;

	void updateScore(bool isCoin, const int level);
	void resetCoins();


private:
	void move(Controller& controller);
	bool enemyCollisionCheck(Controller& controller);
	bool coinCollsionCheck(Controller& controller);

	bool canMoveRightLeft(Controller& controller, const Location& location);
	bool canMoveUpDown(Controller& controller, const Location& location);

	Location m_location = Location(0, 0);
	int m_lives = LIVES;
	int m_coins = 0;
	int m_score = 0;
};
