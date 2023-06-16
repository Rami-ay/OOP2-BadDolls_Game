#pragma once
#include "GameObject.h"


class MovingObject : public GameObject
{
public:
	MovingObject(const sf::Sprite&);
	virtual ~MovingObject() = default;
	virtual void update(sf::Time) = 0;
	virtual void direction(sf::Keyboard::Key key) = 0;
	
	int getHealth();
    void setHealth(int h) ;
	void decreaseHealth(int h);
	bool isDead();
private:
	sf::Vector2f m_prevPosition;
	int m_health;
};