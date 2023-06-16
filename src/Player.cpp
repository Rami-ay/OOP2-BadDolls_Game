#include "Player.h"

Player::Player(const sf::Sprite& sprite) :MovingObject(sprite),m_coins(0), m_points(0)
{
}

int Player::getCoins()
{
	return m_coins;
}

void Player::setCoins(int c)
{
	m_coins += c;
}

int Player::getPoints()
{
	return m_points;
}

void Player::setPoints(int p)
{
	m_points += p;
}

void Player::addGun(Gun gun)
{
   
	m_guns.push_back(gun);
}

Gun Player::getGun(int index)
{
	if (index < 0 || index >= m_guns.size())
	{
		throw std::out_of_range("Invalid gun index");
	}

	return m_guns[index];
}

int Player::getGunCount()
{
	return m_guns.size();
}


void Player::changeGunsDirection(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Right)
    {
        for (auto& gun : m_guns)
        {
            gun.getSprite().setOrigin(0.f, gun.getSprite().getLocalBounds().height / 2);
            gun.getSprite().setScale(1.f, 1.f);
        }
    }
    else if (key == sf::Keyboard::Left)
    {
        for (auto& gun : m_guns)
        {
            gun.getSprite().setOrigin(gun.getSprite().getLocalBounds().width, gun.getSprite().getLocalBounds().height / 2);
            gun.getSprite().setScale(-1.f, 1.f);
        }
    }
}



