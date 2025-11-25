#pragma once
#include "Board.h"
#include "Enemy.h"
#include "Player.h"
#include <vector>

class Controller
{
public:
    Controller() = default;
    void run();

    int getWidth() const;
    int getHeight() const;
    int getLevel() const;
    int getNumberOfEnemies() const;
    char getCellAtLocation(const Location& location) const;

    const Location& getPlayerLocation() const;
    const Location& getEnemyLocation(int i) const;

    bool validLocationInBoard(const Location& location) const;

    bool removeCoin(const Location& location);
    void drawCellAtLocation(char cell, const Location& location) const;

private:
    bool m_running = true;
    Board m_board;
    Player m_player;
    std::vector<Enemy> m_enemyList;

    void resetLevel();
    void loadNextLevel();
    void setEntitiesStartingLocation();
    void drawGame() const;
    void updateGame();
    void gameOverScreen(bool win) const;
    void handlePlayerHit();
};