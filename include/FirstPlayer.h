#pragma once

#include "MovingObject.h"
#include "Character.h"
#include <memory>
#include "Animation.h"
#include "Resources.h"
#include "Player.h"

class FirstPlayer : public Player
{
public:
	FirstPlayer(const sf::Sprite& sprite, sf::Vector2f b2dPos, std::unique_ptr<b2World>& world);
	void update(sf::Time);
	virtual void direction(sf::Keyboard::Key key) override;

	void addHealth(int h);

private:
	std::unique_ptr<Character> m_playerCharacter;
	Direction m_dir = Direction::Stay;
	Animation m_animation;
	b2Body* m_b2dBody;
};