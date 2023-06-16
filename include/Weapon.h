#pragma once

#include "Item.h"

class Weapon : public Item
{
public:
	Weapon() {};
	//virtual void initItem(sf::Vector2f position, sf::Sprite spritechar) override;
private:

	sf::Sprite m_sprite;
};