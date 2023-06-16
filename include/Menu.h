#pragma once


// -- - includes-- -
#include <SFML/Graphics.hpp>
#include "io.h"



class Menu
{
public:
	virtual ClickedButton handleClick(const sf::Event::MouseButtonEvent& event, sf::RenderWindow* window) = 0;
	virtual void handleHoverOver(sf::RenderWindow* window) = 0;
	virtual ClickedButton displayMenu(sf::RenderWindow* window) = 0;
};