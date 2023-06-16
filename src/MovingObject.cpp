#include "MovingObject.h"
#include <iostream>

MovingObject::MovingObject(const sf::Sprite& sprite):GameObject(sprite) {}
int MovingObject::getHealth()
{
    return m_health;
}
void MovingObject::setHealth(int h)
{
    m_health = h;
}
void MovingObject::decreaseHealth(int h)
{
    m_health -= h;
}
bool MovingObject::isDead()
{
    return m_health <= 0;
}
//-------------------------------------------------------------------------------------------


