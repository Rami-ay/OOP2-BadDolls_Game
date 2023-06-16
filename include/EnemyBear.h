#pragma once

#include "MovingObject.h"
#include <memory>
#include "Animation.h"
#include "Resources.h"
#include "Enemy.h"
#include <optional>
#include "Direction.h"

class EnemyBear : public Enemy
{
public:
	EnemyBear(const sf::Sprite&);
	virtual void update(sf::Time) override;
	virtual void direction(sf::Keyboard::Key key) override;

private:
	std::unique_ptr<Character> m_playerCharacter;
	Direction m_dir = Direction::Stay;
	Animation m_animation;
};