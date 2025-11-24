#pragma once

#include "Location.h"
#include <vector>

class Controller;

class Enemy
{
public:
	Enemy() = default;
	Enemy(const Location& location);
	void move(Controller& controller);

	void draw(Controller& controller);
	void setLocation(const Location& location);
	const Location& getLocation() const;

private:
	Location m_location = Location(0, 0);

	// Path storage
	std::vector<Location> m_path;

	// Helper to determine if a specific move is valid
	bool isValidMove(Controller& controller, const Location& from, const Location& to);

	// Core A* function
	void calculatePathToPlayer(Controller& controller);

	// Helper for dumb movement
	void moveRandomly(Controller& controller);
};