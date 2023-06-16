#pragma once

// --- includes --- 
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "io.h"

class HelpWindow
{
public:
	HelpWindow();
	void help_run();
	

private:

	sf::Text m_text;
	//back button:
	Button m_back_button;
	sf::RenderWindow m_tempWindow;


	bool back_click(const sf::Event::MouseButtonEvent& event);
};