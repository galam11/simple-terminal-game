#include "Enemy.h"
#include "Controller.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

Enemy::Enemy(const Location& location)
    : m_location(location)
{
}

void Enemy::setLocation(const Location& location)
{
    m_location = location;
}

const Location& Enemy::getLocation() const
{
    return m_location;
}

void Enemy::draw(const Controller& controller) const
{
    controller.drawCellAtLocation(ENEMY, m_location);
}

void Enemy::move(const Controller& controller)
{
    if (std::rand() % 100 < 30)
    {
        moveRandom(controller);
    }
    else
    {
        moveSmart(controller);
    }
}

void Enemy::moveSmart(const Controller& controller)
{
    Location goal = controller.getPlayerLocation();
    std::vector<Location> path = findPathAStar(controller, m_location, goal);

    if (!path.empty())
    {
        setLocation(path.front());
    }
}

void Enemy::moveRandom(const Controller& controller)
{
    std::vector<Location> neighbors = getValidNeighbors(controller, m_location);

    if (!neighbors.empty())
    {
        int randomIndex = std::rand() % (int)neighbors.size();
        setLocation(neighbors[randomIndex]);
    }
}

std::vector<Location> Enemy::findPathAStar(const Controller& controller, const Location& start, const Location& goal) const
{
    if (start == goal) return {};

    int height = controller.getHeight();
    int width = controller.getWidth();
    const double INF = 999999.0;

    std::vector<std::vector<double>> gScore(height, std::vector<double>(width, INF));
    std::vector<std::vector<Location>> cameFrom(height, std::vector<Location>(width, { -1, -1 }));
    std::vector<Location> openSet;

    gScore[start.row][start.col] = 0;
    openSet.push_back(start);

    while (!openSet.empty())
    {
        int bestIndex = -1;
        double minF = INF;

        for (int i = 0; i < (int)openSet.size(); ++i)
        {
            Location node = openSet[i];
            double f = gScore[node.row][node.col] + estimatedDistance(node, goal);

            if (f < minF)
            {
                minF = f;
                bestIndex = i;
            }
        }

        if (bestIndex == -1) break;

        Location current = openSet[bestIndex];

        if (current == goal)
        {
            std::vector<Location> path;
            Location curr = goal;
            while (!(curr == start))
            {
                path.push_back(curr);
                curr = cameFrom[curr.row][curr.col];
            }

            int n = (int)path.size();
            for (int i = 0; i < n / 2; ++i)
            {
                Location temp = path[i];
                path[i] = path[n - 1 - i];
                path[n - 1 - i] = temp;
            }

            return path;
        }

        openSet.erase(openSet.begin() + bestIndex);

        std::vector<Location> neighbors = getValidNeighbors(controller, current);

        for (int i = 0; i < (int)neighbors.size(); ++i)
        {
            Location neighbor = neighbors[i];
            double tentativeG = gScore[current.row][current.col] + 1;

            if (tentativeG < gScore[neighbor.row][neighbor.col])
            {
                cameFrom[neighbor.row][neighbor.col] = current;
                gScore[neighbor.row][neighbor.col] = tentativeG;

                bool inOpenSet = false;
                for (int j = 0; j < (int)openSet.size(); ++j)
                {
                    if (openSet[j] == neighbor)
                    {
                        inOpenSet = true;
                        break;
                    }
                }

                if (!inOpenSet)
                {
                    openSet.push_back(neighbor);
                }
            }
        }
    }
    return {};
}

std::vector<Location> Enemy::getValidNeighbors(const Controller& controller, const Location& current) const
{
    std::vector<Location> neighbors;
    Location directions[] = { current.up(), current.down(), current.left(), current.right() };

    for (int i = 0; i < 4; ++i)
    {
        Location dir = directions[i];
        if (isValidMove(controller, current, dir))
        {
            neighbors.push_back(dir);
        }
    }
    return neighbors;
}

bool Enemy::isValidMove(const Controller& controller, const Location& from, const Location& to) const
{
    if (!controller.validLocationInBoard(to)) return false;

    char currentCell = controller.getCellAtLocation(from);
    char targetCell = controller.getCellAtLocation(to);
    bool isVertical = (from.col == to.col);

    if (isVertical) return (currentCell == LADDER && targetCell == LADDER);
    if (targetCell == FLOOR) return false;

    Location belowTarget = to.down();
    if (controller.validLocationInBoard(belowTarget))
    {
        char cellBelow = controller.getCellAtLocation(belowTarget);
        if (targetCell == LADDER || targetCell == RAIL || cellBelow == FLOOR || cellBelow == LADDER)
        {
            return true;
        }
    }
    return false;
}

double Enemy::estimatedDistance(const Location& a, const Location& b) const
{
    return std::abs(a.row - b.row) + std::abs(a.col - b.col);
}