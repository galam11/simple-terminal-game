#pragma once
#include "Location.h"
#include <vector>

class Controller;

class Enemy
{
public:
    Enemy(const Location& location);

    void move(const Controller& controller);

    void draw(const Controller& controller) const;
    void setLocation(const Location& location);
    const Location& getLocation() const;

private:
    Location m_location;

    void moveSmart(const Controller& controller);
    void moveRandom(const Controller& controller);

    // --- Pathfinding (A*) Helpers ---
    std::vector<Location> findPathAStar(const Controller& controller, const Location& start, const Location& goal) const;
    std::vector<Location> getValidNeighbors(const Controller& controller, const Location& current) const;
    bool isValidMove(const Controller& controller, const Location& from, const Location& to) const;
    double estimatedDistance(const Location& a, const Location& b) const;
};