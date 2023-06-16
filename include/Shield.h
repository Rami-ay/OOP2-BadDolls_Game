#pragma once

#include "Item.h"

class Shield : public Item
{
public:
	Shield() {};
	//virtual void initItem(sf::Vector2f position, sf::Sprite spritechar) override;
private:

	sf::Sprite m_sprite;
};