#include <Board.h>
#include <Location.h>
#include <iostream>


Board::Board()
{
	m_inputStreem.open(FILE_PATH);
}

Board::~Board()
{
	m_inputStreem.close();
}

bool Board::loadNext()
{
	m_level++;

	std::string buffer;
	std::getline(m_inputStreem, buffer);

	if (buffer.empty())
		return false;

	m_levelHight = std::stoi(buffer);

	m_BoardData.clear();

	for (int i = 0; i < m_levelHight; i++) 
	{
		std::getline(m_inputStreem, buffer);
		m_BoardData.push_back(buffer);
	}
	m_width = m_BoardData[0].length();
	saveEntitisState();

	return true;
}

void Board::saveEntitisState()
{
	for (int i = 0; i < m_levelHight; i++)
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
			default:
				break;
			}
		}
}



void Board::drawLevel() const
{
	for (int i = 0; i < m_levelHight; i++)
		std::cout << m_BoardData[i] << '\n';
}

char Board::getAt(const Location& location) const
{
	return m_BoardData[location.col][location.row];
}

int Board::getWidth() const
{
	return m_width;
}

int Board::getHight() const
{
	return m_levelHight;
}

int Board::getLevel() const
{
	return m_level;
}