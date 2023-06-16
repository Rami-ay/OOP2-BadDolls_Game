#pragma once
#include "io.h"
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Animation.h"
class GameObject
{
public:
	GameObject(const sf::Sprite&);
	virtual ~GameObject() = default;

	sf::Sprite& getSprite();
	void setSprite(sf::Sprite);

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f);

	void setPrevPosition(sf::Vector2f pos);
	sf::Vector2f getPrevPosition() const;

	//virtual void initObject(int currentCol, int currentRow, sf::Sprite newSprite) = 0;
	void draw(sf::RenderWindow* window);

	b2Body* getB2DBody();

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_prevPosition;
	b2Body* m_b2dBody;
};