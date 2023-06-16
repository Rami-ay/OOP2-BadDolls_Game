#pragma once
#include "Menu.h"
#include "Button.h"
#include "io.h"
#include "Resources.h"
#include "HelpWindow.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cctype>


class StartMenu : public Menu
{
public:
	StartMenu() {};
	~StartMenu() {};
	void setStartMenu();
	virtual ClickedButton displayMenu(sf::RenderWindow* window) override;
	std::string getPlayerName() const;

private:
	//vector contains all the buttons
	std::vector<Button> m_buttons;
	Button m_backButton;
	//background sprite:
	sf::Sprite m_bgSprite;

	//help menu:
	HelpWindow m_helpWindow;

	sf::RectangleShape m_nameBackGround;
	sf::Text m_playerName;

	std::string m_finalPlayerName;

	virtual ClickedButton handleClick(const sf::Event::MouseButtonEvent& event, sf::RenderWindow* window) override;
	virtual void handleHoverOver(sf::RenderWindow* window) override;
	void handleTextInput(sf::RenderWindow* window);
	void setupNameInput();
};







//
//
//
//class StartMenu /*: public Menu*/
//{
//public:
//	
//	StartMenu();
//	~StartMenu() {};
//	void setStartMenu();
//	/*virtual ClickedButton displayMenu(sf::RenderWindow* window) override;*/
//
//private:
//	Button m_logInButton;
//	Button m_helpButton;
//	Button m_exitButton;
//
//	sf::Texture m_bgImage;
//	sf::Sprite m_bgSprite;
//
//	virtual ClickedButton handleClick(const sf::Event::MouseButtonEvent& event, sf::RenderWindow* window) override;
//	virtual void handleHoverOver(sf::RenderWindow* window) override;
//
//};
//
