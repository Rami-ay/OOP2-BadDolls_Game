#pragma once

#include "EnemyCharacter.h"

class Enemy_Character_Type3 : public EnemyCharacter
{
public:
	//default c-tor;
	Enemy_Character_Type3();
	//initiate character:
	virtual void initEnemyCharacter(sf::Vector2f position, sf::Sprite spritechar) override;

private:

};