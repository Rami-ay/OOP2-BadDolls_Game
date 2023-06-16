#pragma once

#include "MovingObject.h"
#include "Character.h"
#include <memory>
#include "Animation.h"
#include "Resources.h"
#include "io.h"
#include "Gun.h"
class Player : public MovingObject
{
public:
	Player() = default;
	Player(const sf::Sprite&);
	virtual void update(sf::Time) = 0;
	virtual void direction(sf::Keyboard::Key key) = 0;

	int getCoins();
	void setCoins(int);

	int getPoints();
	void setPoints(int);

	void addGun(Gun gun);
	Gun getGun(int index);
	int getGunCount();
	void changeGunsDirection(sf::Keyboard::Key key);

private:
	int m_coins;
	int m_points;
	std::vector<Gun> m_guns;
};