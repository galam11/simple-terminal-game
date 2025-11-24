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
	void draw(Controller& controller);
	
	void setLocation(const Location& location);
	const Location& getLocation() const;
	
	const int getLives() const;

	void updateScore(bool isCoin, const int level);
	int getScore();

	void resetCoins();
	const int getCoins() const;


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
