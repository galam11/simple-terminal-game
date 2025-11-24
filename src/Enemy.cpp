#include "Enemy.h"
#include "Controller.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

Enemy::Enemy(const Location& location)
	: m_location(location) {
}

void Enemy::move(Controller& controller)
{
	// 30% chance to make a random move instead of a smart one.
	if (std::rand() % 100 < 30)
	{
		moveRandomly(controller);
		return;
	}

	calculatePathToPlayer(controller);

	if (!m_path.empty())
	{
		Location nextStep = m_path.front();

		if (controller.movableLocation(nextStep))
		{
			setLocation(nextStep);
		}

		m_path.clear();
	}
}

void Enemy::moveRandomly(Controller& controller)
{
	std::vector<Location> validMoves;

	Location neighbors[] = {
		m_location.up(),
		m_location.down(),
		m_location.left(),
		m_location.right()
	};

	for (int i = 0; i < 4; i++)
	{
		Location neighbor = neighbors[i];

		if (isValidMove(controller, m_location, neighbor))
		{
			validMoves.push_back(neighbor);
		}
	}

	if (!validMoves.empty())
	{
		int randomIndex = std::rand() % validMoves.size();
		setLocation(validMoves[randomIndex]);

		m_path.clear();
	}
}

void Enemy::draw(Controller& controller)
{
	controller.drawCellAtLocation(ENEMY, m_location);
}

void Enemy::setLocation(const Location& location)
{
	m_location = location;
}

const Location& Enemy::getLocation() const
{
	return m_location;
}

// --- Pathfinding Logic ---

bool Enemy::isValidMove(Controller& controller, const Location& from, const Location& to)
{
	if (!controller.validLocationInBoard(to))
		return false;

	bool isVertical = (from.col == to.col);
	bool isHorizontal = (from.row == to.row);

	char currentCell = controller.getCellAtLocation(from);
	char targetCell = controller.getCellAtLocation(to);

	if (isVertical)
	{
		return (currentCell == LADDER && targetCell == LADDER);
	}

	if (isHorizontal)
	{
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
	}

	return false;
}

void Enemy::calculatePathToPlayer(Controller& controller)
{
	Location start = m_location;
	Location goal = controller.getPlayerLocation();

	if (start == goal) return;

	int height = controller.getHeight();
	int width = controller.getWidth();

	const double INF_COST = 999999.0;

	std::vector<std::vector<double>> gScore(height, std::vector<double>(width, INF_COST));
	std::vector<std::vector<Location>> cameFrom(height, std::vector<Location>(width, Location{ -1, -1 }));
	std::vector<Location> openSet;

	gScore[start.row][start.col] = 0;
	openSet.push_back(start);

	while (!openSet.empty())
	{
		int bestNodeIndex = 0;
		double minF = INF_COST;

		for (int i = 0; i < openSet.size(); ++i)
		{
			Location loc = openSet[i];

			double g = gScore[loc.row][loc.col];
			double h = std::abs(loc.row - goal.row) + std::abs(loc.col - goal.col);
			double f = g + h;

			if (f < minF)
			{
				minF = f;
				bestNodeIndex = i;
			}
		}

		Location current = openSet[bestNodeIndex];

		openSet[bestNodeIndex] = openSet.back();
		openSet.pop_back();

		if (current == goal)
		{
			m_path.clear();
			Location curr = goal;
			while (!(curr == start))
			{
				m_path.push_back(curr);
				curr = cameFrom[curr.row][curr.col];
			}

			int n = m_path.size();
			for (int i = 0; i < n / 2; ++i)
			{
				Location temp = m_path[i];
				m_path[i] = m_path[n - 1 - i];
				m_path[n - 1 - i] = temp;
			}

			return;
		}

		Location neighbors[4];
		neighbors[0] = current.up();
		neighbors[1] = current.down();
		neighbors[2] = current.left();
		neighbors[3] = current.right();

		for (int i = 0; i < 4; ++i)
		{
			Location neighbor = neighbors[i];

			if (isValidMove(controller, current, neighbor))
			{
				double newG = gScore[current.row][current.col] + 1;

				if (newG < gScore[neighbor.row][neighbor.col])
				{
					cameFrom[neighbor.row][neighbor.col] = current;
					gScore[neighbor.row][neighbor.col] = newG;

					bool inOpenSet = false;
					for (int j = 0; j < openSet.size(); ++j)
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
	}
}