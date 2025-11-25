#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "Location.h"
#include "macros.h"


class Board
{
public:
    Board();
    ~Board();

    bool loadNext();
    void draw() const;

    char getAt(const Location& location) const;
    int getWidth() const;
    int getHeight() const;
    int getLevel() const;
    int getCoinsInLevel() const;
    int getEnemiesCount() const;

    const Location& getPlayerStartLocation() const;
    const Location& getEnemyStartLocation(int i) const;

    bool removeCoin(const Location& location);
    bool LocationInBounds(const Location& location) const;

private:
    int m_level = 0;
    int m_width = 0, m_levelHeight = 0;
    std::vector<std::string> m_boardData;
    int m_coinsInLevel;

    std::vector<Location> m_enemiesStartLocations;
    Location m_playerStartLocation = Location(0, 0);

    std::ifstream m_inputStream;

    void saveEntityState();
};