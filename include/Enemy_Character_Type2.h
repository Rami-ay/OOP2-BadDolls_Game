#pragma once

#include "EnemyCharacter.h"

class Enemy_Character_Type2 : public EnemyCharacter
{
public:
	//default c-tor;
	Enemy_Character_Type2();
	//initiate character:
	virtual void initEnemyCharacter(sf::Vector2f position, sf::Sprite spritechar) override;

private:

};