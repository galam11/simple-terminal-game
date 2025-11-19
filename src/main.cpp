#include <iostream>
#include <Level.h>
#include <Location.h>


int main()
{
	Level level;

	level.loadNext();

	std::cout 
		<< level.getCurrentLevel() << " "
		<< level.getLevelHight() << " "
		<< level.getLevelWidth() << " "
		<< std::endl;

	level.drawLevel();

	level.loadNext();
	std::cout 
		<< level.getCurrentLevel() << " "
		<< level.getLevelHight() << " "
		<< level.getLevelWidth() << " "
		<< std::endl;

	level.drawLevel();

	return 0;
}
