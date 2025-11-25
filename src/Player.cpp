#include "Player.h"
#include "Controller.h"
#include "io.h"
#include <iostream>
#include <conio.h> 

Player::Player(const Location& location) : m_location(location) {}

void Player::setLocation(const Location& location) { m_location = location; }
const Location& Player::getLocation() const { return m_location; }
int Player::getLives() const { return m_lives; }
int Player::getScore() const { return m_score; }
int Player::getCoins() const { return m_coins; }

void Player::updateScore(bool isCoin, int level)
{
    m_score += ((isCoin) ? COIN_SCORE : LEVEL_WON_SCORE) * level;
}

void Player::resetCoins() { m_coins = 0; }

bool Player::update(Controller& controller)
{
    if (checkEnemyCollision(controller)) return false;

    handleInputAndMove(controller);
    checkCoinCollision(controller);

    if (checkEnemyCollision(controller)) return false;

    return true;
}

void Player::draw() const
{
	Screen::setLocation(m_location);
	std::cout << PLAYER;
}

void Player::handleInputAndMove(const Controller& controller)
{
    while (true)
    {
        int input = _getch();
        if (input == Keys::SPECIAL_KEY || input == 0)
            input = _getch();

        Location nextLocation = m_location;

        switch (input)
        {
        case SpecialKeys::RIGHT:
            nextLocation = m_location.right();
            if (!canMoveHorizontal(controller, nextLocation)) continue;
            break;
        case SpecialKeys::LEFT:
            nextLocation = m_location.left();
            if (!canMoveHorizontal(controller, nextLocation)) continue;
            break;
        case SpecialKeys::DOWN:
            nextLocation = m_location.down();
            if (!canMoveVertical(controller, nextLocation)) continue;
            break;
        case SpecialKeys::UP:
            nextLocation = m_location.up();
            if (!canMoveVertical(controller, nextLocation)) continue;
            break;
        case SpecialKeys::SPACE_BAR:
            break;
        default:
            continue; // Invalid key, wait for next input
        }

        setLocation(nextLocation);
        break; // Move successful
    }
}

bool Player::canMoveHorizontal(const Controller& controller, const Location& location) const
{
    if (!controller.validLocationInBoard(location)) return false;

    Location below = location.down();
    if (controller.validLocationInBoard(below))
    {
        char cellBelow = controller.getCellAtLocation(below);
        char currentCell = controller.getCellAtLocation(location);

        // Cannot fall through floor, can move if on ladder or supported by floor/ladder
        if (((cellBelow == FLOOR || cellBelow == LADDER) && currentCell != FLOOR) || currentCell == LADDER)
            return true;
    }

    return controller.getCellAtLocation(location) == RAIL;
}

bool Player::canMoveVertical(const Controller& controller, const Location& location) const
{
    return controller.validLocationInBoard(location)
        && controller.getCellAtLocation(location) == LADDER
        && controller.getCellAtLocation(m_location) == LADDER;
}

bool Player::checkEnemyCollision(const Controller& controller)
{
    for (int i = 0; i < controller.getNumberOfEnemies(); i++)
    {
        if (m_location == controller.getEnemyLocation(i))
        {
            m_lives--;
            return true;
        }
    }
    return false;
}

bool Player::checkCoinCollision(Controller& controller)
{
    if (controller.removeCoin(m_location))
    {
        m_coins++;
        updateScore(true, controller.getLevel());
        return true;
    }
    return false;
}