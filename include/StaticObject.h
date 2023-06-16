#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"


class StaticObject : public GameObject
{
public:
	//virtual void initItem(sf::Vector2f position, sf::Sprite spritechar) = 0;
	StaticObject(const sf::Sprite&);

	void deleteObject();
	bool getDelete();

private:
	bool m_delete;
};