#pragma once
#include "StaticObject.h"
#include "Item.h"
#include <memory>

class Gift : public StaticObject
{
public:
	Gift(const sf::Sprite&);
	//virtual void setActivated(bool status) = 0;
	//virtual bool getActivated() const = 0;

private:
	//bool m_activated = false;
	//std::unique_ptr<Item> m_item;

};