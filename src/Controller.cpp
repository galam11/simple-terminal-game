#include "Controller.h"
#include "io.h"
#include <iostream>

void Controller::run()
{
    loadNextLevel();
    drawGame();

    while (m_running)
    {
        updateGame();
        drawGame();
    }
    gameOverScreen(true);
}

void Controller::updateGame()
{
    if (!m_player.update(*this))
        handlePlayerHit();

    for (int i = 0; i < (int)m_enemyList.size(); ++i)
    {
        m_enemyList[i].move(*this);
    }

    if (m_board.getCoinsInLevel() == m_player.getCoins())
        loadNextLevel();
}

void Controller::drawGame() const
{
    Screen::resetLocation();
    m_board.draw();
    m_player.draw();

    for (int i = 0; i < (int)m_enemyList.size(); ++i)
    {
        m_enemyList[i].draw();
    }

    Screen::setLocation(Location(m_board.getHeight(), 0));
    std::cout << "Lives: " << m_player.getLives()
        << "  Level: " << getLevel()
        << "  Score: " << m_player.getScore() << std::endl;
}

void Controller::loadNextLevel()
{
    m_player.updateScore(false, getLevel());

    if ((m_running = m_board.loadNext()))
    {
        Screen::resetLocation();
        system("cls");
        m_enemyList.clear();

        int enemyCount = m_board.getEnemiesCount();
        m_enemyList.resize(enemyCount, Enemy(Location(0, 0)));

        setEntitiesStartingLocation();
        m_player.resetCoins();
    }
    else
    {
        Screen::resetLocation();
        system("cls");
    }
}

void Controller::setEntitiesStartingLocation()
{
    m_player.setLocation(m_board.getPlayerStartLocation());
    for (int i = 0; i < (int)m_enemyList.size(); i++)
    {
        m_enemyList[i].setLocation(m_board.getEnemyStartLocation(i));
    }
}

void Controller::handlePlayerHit()
{
    if (m_player.getLives() == 0)
    {
        gameOverScreen(false);
        exit(EXIT_SUCCESS);
    }
    else
    {
        resetLevel();
    }
}

void Controller::resetLevel()
{
    Screen::resetLocation();
    m_board.draw();
    setEntitiesStartingLocation();
}

void Controller::gameOverScreen(bool win) const
{
    Screen::resetLocation();
    system("cls");
    std::cout << "Game Over! " << (win ? "You Won!" : "You Lost!")
        << "\n\t Score: " << m_player.getScore() << std::endl;
}

// --- Passthrough Helpers ---

int Controller::getWidth() const { return m_board.getWidth(); }

int Controller::getHeight() const { return m_board.getHeight(); }

int Controller::getLevel() const { return m_board.getLevel(); }

int Controller::getNumberOfEnemies() const { return (int)m_enemyList.size(); }

char Controller::getCellAtLocation(const Location& location) const { return m_board.getAt(location); }

const Location& Controller::getPlayerLocation() const { return m_player.getLocation(); }

const Location& Controller::getEnemyLocation(int i) const { return m_enemyList[i].getLocation(); }

bool Controller::validLocationInBoard(const Location& location) const { return m_board.LocationInBounds(location); }

bool Controller::removeCoin(const Location& location) { return m_board.removeCoin(location); }