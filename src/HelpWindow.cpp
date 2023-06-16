#include "HelpWindow.h"
#include <SFML/Graphics.hpp>

//constructor:
HelpWindow::HelpWindow()
{
	// Initialize the window and any other necessary resources
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	sf::Vector2u m_tempWindowSize(400, 300);
	sf::Vector2u m_tempWindowPosition(
		(desktopMode.width - m_tempWindowSize.x) / 2,
		(desktopMode.height - m_tempWindowSize.y) / 2
	);
	m_tempWindow.create(sf::VideoMode(m_tempWindowSize.x, m_tempWindowSize.y), "Game Instructions");
	m_tempWindow.setPosition(sf::Vector2i(m_tempWindowPosition.x, m_tempWindowPosition.y));


	m_text.setString("HELP INSTRUCTIONS, FILL ME LATER");
	m_text.setFillColor(sf::Color::Blue);

	//set the font:
	m_text.setFont(getGlobalFont());

	//set back button:
	m_back_button.setButtonInfo("Back", { 0.2 * BOARD_WIDTH, 0.12 * BOARD_HEIGHT }, 0.05 * BOARD_HEIGHT, sf::Color::Transparent, sf::Color::Red,
		{ 0.4 * BOARD_WIDTH,0.68 * BOARD_HEIGHT }, getGlobalFont());

}
//-------------------------------------------------------------------------------------------
void HelpWindow::help_run()
{
	bool condition = false;


	while (m_tempWindow.isOpen() && condition == false)
	{
		//clear window
		m_tempWindow.clear();

		//drwaings:
		//====================================
		m_tempWindow.draw(m_text);


		//draw button:
		m_tempWindow.draw(m_back_button.getbuttonBg());
		m_tempWindow.draw(m_back_button.getext());

		//Display on the window:
		m_tempWindow.display();


		//catching events:
		if (auto event = sf::Event{}; m_tempWindow.waitEvent(event))
		{
			switch (event.type)
			{
				//closing window:
			case sf::Event::Closed:
				m_tempWindow.close();
				break;
				//mouse clicked:
			case sf::Event::MouseButtonReleased:
				condition = back_click(event.mouseButton);
				break;
				//mouse houvering over buttons:
			case sf::Event::MouseMoved:
				// ======== hovering over start button: =========
				if (m_back_button.isMouseOver(m_tempWindow))
				{
					m_back_button.setTextColor(sf::Color::Blue);
				}
				else
					m_back_button.setTextColor(sf::Color::Red);

			}
		}
	}
}
//-------------------------------------------------------------------
//this function handles the back button click:
bool HelpWindow::back_click(const sf::Event::MouseButtonEvent& event)
{
	if (m_back_button.getbuttonBg().getGlobalBounds().contains(
		m_tempWindow.mapPixelToCoords({ event.x, event.y })))
	{
		return true;
	}
	else
		return false;
}
//-------------------------------------------------------------------