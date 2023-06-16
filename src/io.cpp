#include "io.h"


const sf::Font& getGlobalFont()
{
	static sf::Font font;
	static bool isLoaded = false;

	if (!isLoaded)
	{
		if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf"))
		{
			// handle the case when font loading fails
		}
		isLoaded = true;
	}

	return font;
}