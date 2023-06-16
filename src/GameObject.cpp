#include "GameObject.h"

GameObject::GameObject(const sf::Sprite& sprite):m_sprite(sprite){}
//-------------------------------------------------------------------------------------------
//return the sprite:
sf::Sprite& GameObject::getSprite() 
{
    return m_sprite;
}
//-------------------------------------------------------------------------------------------
//set sprite:
void GameObject::setSprite(sf::Sprite sprite)
{
    m_sprite = sprite;
}
//-------------------------------------------------------------------------------------------
//get sprite position:
sf::Vector2f GameObject::getPosition() const
{
    return m_sprite.getPosition();
}
//-------------------------------------------------------------------------------------------
//set sprite position:
void GameObject::setPosition(sf::Vector2f position)
{
    m_sprite.setPosition(position);
}
//-------------------------------------------------------------------------------------------
//draw object to the window:
void GameObject::draw(sf::RenderWindow* window)
{
    window->draw(m_sprite);
}
//-------------------------------------------------------------------------------------------
//set the previouse position:
void GameObject::setPrevPosition(sf::Vector2f pos)
{
    m_prevPosition = pos;
}
//-------------------------------------------------------------------------------------------
//get the previouse position:
sf::Vector2f GameObject::getPrevPosition() const
{
    return m_prevPosition;
}
//-------------------------------------------------------------------------------------------
b2Body* GameObject::getB2DBody()
{
    return m_b2dBody;
}