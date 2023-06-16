#pragma once
#include <SFML/Graphics.hpp>
#include "io.h"
class Character
{
public:
	Character() {};
	//function that initiates the character:
	virtual void initCharacter(sf::Vector2f position, sf::Sprite spritechar) = 0;

private:
	sf::Sprite m_char;
};