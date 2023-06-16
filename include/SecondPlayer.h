#pragma once

#include "MovingObject.h"
#include "Character.h"
#include <memory>
#include "Animation.h"
#include "Resources.h"
#include "Player.h"

class SecondPlayer : public Player
{
public:
	SecondPlayer(const sf::Sprite&);

	void update(sf::Time);

	//virtual void moveObject() override;
	//sf::Vector2f getPlayerPosition() const;
	//void setPlayerPosition(sf::Vector2f new_position);
	//virtual void draw(sf::RenderWindow* window) override;
	virtual void direction(sf::Keyboard::Key key) override;

	void addHealth(int h);
private:
	std::unique_ptr<Character> m_playerCharacter;
	Direction m_dir = Direction::Stay;
	Animation m_animation;
};