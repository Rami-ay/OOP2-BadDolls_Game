#pragma once

#include <SFML/Graphics.hpp>

class EnemyCharacter
{
public:
	EnemyCharacter() {};
	//function that initiates the character:
	virtual void initEnemyCharacter(sf::Vector2f position, sf::Sprite spritechar) = 0;

private:
	sf::Sprite m_enemyChar;
};