#pragma once

#include "Item.h"
#include "Gift.h"
#include "Resources.h"

class Coin : public Gift
{
public:
	Coin(const sf::Sprite&);
	void update(sf::Time);
	//virtual void initItem(sf::Vector2f position, sf::Sprite spritechar) override;
private:
	Direction m_dir = Direction::Stay;
	Animation m_animation;
};