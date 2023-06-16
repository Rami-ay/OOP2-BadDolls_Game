#pragma once
#include "StaticObject.h"
#include <memory>

class Wall : public StaticObject
{
public:
		

	Wall(const sf::Sprite&);
	//ObjectTypes getObject()const;

	//virtual void initItem(sf::Vector2f position, sf::Sprite spritechar) override;
};