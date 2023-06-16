#pragma once

#include "Menu.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "io.h"
#include "Resources.h"
#include <iostream>
#include <memory>

class MainMenu : public Menu
{
public:
	MainMenu();
	~MainMenu() {};
	void setMainMenu();
	virtual ClickedButton displayMenu(sf::RenderWindow* window) override;


private:
	//vector contains all the buttons
	std::vector<Button> m_buttons;
	//background sprite:
	sf::Sprite m_bgSprite;


	virtual ClickedButton handleClick(const sf::Event::MouseButtonEvent& event, sf::RenderWindow* window) override;
	virtual void handleHoverOver(sf::RenderWindow* window) override;
};
