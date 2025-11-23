#include <Board.h>
#include <Location.h>
#include <iostream>


Board::Board()
{
	m_inputStream.open(FILE_PATH);
}

Board::~Board()
{
	m_inputStream.close();
}

void Board::removeCoin(const Location& location)
{
	m_BoardData[location.row][location.col] = EMPTY;
}

bool Board::loadNext()
{
	m_level++;

	std::string buffer;
	std::getline(m_inputStream, buffer);

	if (buffer.empty())
		return false;

	m_levelHeight = std::stoi(buffer);

	m_BoardData.clear();

	for (int i = 0; i < m_levelHeight; i++) 
	{
		std::getline(m_inputStream, buffer);
		m_BoardData.push_back(buffer);
	}
	m_width = m_BoardData[0].length();
	saveEntityState();

	return true;
}

void Board::saveEntityState()
{
	m_enemiesStartLocations.clear();
	m_coinsInLevel = 0;
	for (int i = 0; i < m_levelHeight; i++)
		for (int j = 0; j < m_width; j++)
		{
			char& charAt = m_BoardData[i][j];
			switch (charAt) {
			case ENEMY:
				charAt = EMPTY;
				m_enemiesStartLocations.push_back(Location(i, j));
				break;
			case PLAYER:
				charAt = EMPTY;
				m_playerStartLocation = Location(i, j);
				break;
			case COIN:
				m_coinsInLevel++;
			default:
				break;
			}
		}
}



void Board::draw() const
{
	for (int i = 0; i < m_levelHeight; i++)
		std::cout << m_BoardData[i] << '\n';
}

bool Board::LocationInBounds(const Location& location) const
{
	return 
		location.col < getWidth()
		&& location.col >= 0 
		&& location.row < getHeight() 
		&& location.row > 0;

}

char Board::getAt(const Location& location) const
{
	return m_BoardData[location.row][location.col];
}

int Board::getWidth() const
{
	return m_width;
}

int Board::getHeight() const
{
	return m_levelHeight;
}

int Board::getLevel() const
{
	return m_level;
}

const Location& Board::getPlayerStartLocation() const
{
	return m_playerStartLocation;
}

const Location& Board::getEnemyStartLocation(int i) const
{
	return m_enemiesStartLocations[i];
}

int Board::getEnemiesCount() const
{
	return m_enemiesStartLocations.size();
}

int Board::getCoinsInLevel() const
{
	return m_coinsInLevel;
}