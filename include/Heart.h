#pragma once

#include "Item.h"
#include "Gift.h"
#include "Resources.h"

class Heart : public Gift
{
public:
	Heart(const sf::Sprite&);
	void update(sf::Time);
	//virtual void initItem(sf::Vector2f position, sf::Sprite spritechar) override;
private:
	Direction m_dir = Direction::Stay;
	Animation m_animation;
};