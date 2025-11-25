#pragma once
#include "Location.h"
#include "macros.h"

class Controller;

class Player
{
public:
    Player() = default;
    Player(const Location& location);

    // Returns true if player is still alive
    bool update(Controller& controller);
    void draw(const Controller& controller) const;

    void setLocation(const Location& location);
    const Location& getLocation() const;

    int getLives() const;
    int getScore() const;
    int getCoins() const;

    void updateScore(bool isCoin, int level);
    void resetCoins();


    void handleInputAndMove(const Controller& controller);
    bool checkEnemyCollision(const Controller& controller);
    bool checkCoinCollision(Controller& controller);

    bool canMoveHorizontal(const Controller& controller, const Location& location) const;
    bool canMoveVertical(const Controller& controller, const Location& location) const;
	bool canMoveUpDown(Controller& controller, const Location& location);

    Location m_location = { 0, 0 };
    int m_lives = LIVES;
    int m_coins = 0;
    int m_score = 0;
};