#pragma once

#include "Character.h"

class Character_Type2 : public Character
{
public:
	//default c-tor;
	Character_Type2();
	//initiate character:
	virtual void initCharacter(sf::Vector2f position, sf::Sprite spritechar) override;

private:
	
};