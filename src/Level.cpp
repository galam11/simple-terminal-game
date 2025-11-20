#include <Level.h>
#include <Location.h>
#include <iostream>




Level::Level()
{
	m_inputStreem.open(FILE_PATH);
}

Level::~Level()
{
	m_inputStreem.close();
}

void Level::loadNext()
{
	m_levelIndex++;

	std::string buffer;
	std::getline(m_inputStreem, buffer);
	m_levelHight = std::stoi(buffer);

	m_levelData.clear();

	for (int i = 0; i < m_levelHight; i++) 
	{
		std::getline(m_inputStreem, buffer);
		m_levelData.push_back(buffer);
	}
	m_levelWidth = m_levelData[0].length();

	
	

}

void Level::saveEntitisState()
{
	for (int i = 0; i < m_levelHight; i++)
		for (int j = 0; j < m_levelWidth; j++)
		{
			char& charAt = m_levelData[i][j];
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



void Level::drawLevel() const
{
	for (int i = 0; i < m_levelHight; i++)
		std::cout << m_levelData[i] << '\n';
}

char Level::getAt(const Location& location) const
{
	return m_levelData[location.col][location.row];
}

int Level::getLevelWidth() const
{
	return m_levelWidth;
}

int Level::getLevelHight() const
{
	return m_levelHight;
}

int Level::getCurrentLevel() const
{
	return m_levelIndex;
}