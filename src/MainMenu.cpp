#include "MainMenu.h"


//default empty c-tor:
MainMenu::MainMenu(){}
//-------------------------------------------------------------------------------------------
void MainMenu::setMainMenu()
{
	auto& texture = Resources::instance().getTextures()[menuBackGround];
	m_bgSprite = sf::Sprite(texture);

	//setting the start Game in button:
	m_buttons.push_back(Button("Start Game", { 0.2 * BOARD_WIDTH , 0.12 * BOARD_HEIGHT }, 0.05 * BOARD_HEIGHT,
		sf::Color::Transparent, sf::Color::Yellow, { 0.4 * BOARD_WIDTH , 0.2 * BOARD_HEIGHT }, getGlobalFont()));

	//setting the Choose character button:
	m_buttons.push_back(Button("Choose Character", { 0.2 * BOARD_WIDTH , 0.12 * BOARD_HEIGHT }, 0.05 * BOARD_HEIGHT,
		sf::Color::Transparent, sf::Color::Yellow, { 0.4 * BOARD_WIDTH , 0.36 * BOARD_HEIGHT }, getGlobalFont()));
	

	//setting the Profile Check button:
	m_buttons.push_back(Button("Profile Check", { 0.2 * BOARD_WIDTH , 0.12 * BOARD_HEIGHT }, 0.05 * BOARD_HEIGHT,
		sf::Color::Transparent, sf::Color::Yellow, { 0.4 * BOARD_WIDTH , 0.52 * BOARD_HEIGHT }, getGlobalFont()));
	
	//setting the Scores List button:
	m_buttons.push_back(Button("Scores List", { 0.2 * BOARD_WIDTH , 0.12 * BOARD_HEIGHT }, 0.05 * BOARD_HEIGHT,
		sf::Color::Transparent, sf::Color::Yellow, { 0.4 * BOARD_WIDTH , 0.68 * BOARD_HEIGHT }, getGlobalFont()));
	
	
	//setting the exit button:
	m_buttons.push_back(Button("Exit Game", { 0.2 * BOARD_WIDTH, 0.12 * BOARD_HEIGHT }, 0.05 * BOARD_HEIGHT,
		sf::Color::Transparent, sf::Color::Yellow, { 0.4 * BOARD_WIDTH , 0.84 * BOARD_HEIGHT }, getGlobalFont()));


}
//-------------------------------------------------------------------------------------------
ClickedButton MainMenu::displayMenu(sf::RenderWindow* window)
{
	ClickedButton clicked = ClickedButton::Invalid;
	//presenting the diffuclty screen:
	while (window->isOpen())
	{
		//clearing the window
		window->clear();

		// Draw buttons
		window->draw(m_bgSprite);
		for (auto button : m_buttons)
		{
			button.drawTo(*window);
		}
		
		//Display:
		window->display();


		if (auto event = sf::Event{}; window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				exit(EXIT_SUCCESS);
				break;

			case sf::Event::MouseButtonReleased:
				clicked = handleClick(event.mouseButton, window);
				if (clicked != ClickedButton::Invalid)
					return clicked;
				break;
				//mouse houvering over buttons:
			case sf::Event::MouseMoved:
				handleHoverOver(window);
				break;
			}
		}
	}
}
//-------------------------------------------------------------------------------------------
ClickedButton MainMenu::handleClick(const sf::Event::MouseButtonEvent& event, sf::RenderWindow* window)
{
	//if the user pressed the start game button:
	if (m_buttons[0].getbuttonBg().getGlobalBounds().contains(
		window->mapPixelToCoords({ event.x, event.y })))
	{
		return ClickedButton::StartGame;

	}
	//if the user pressed the choose character button:
	if (m_buttons[1].getbuttonBg().getGlobalBounds().contains(
		window->mapPixelToCoords({ event.x, event.y })))
	{
		return ClickedButton::ChooseCharacter;

	}
	//if the user pressed the check profile button:
	if (m_buttons[2].getbuttonBg().getGlobalBounds().contains(
		window->mapPixelToCoords({ event.x, event.y })))
	{
		return ClickedButton::ProfileCheck;
	}
	//if the user pressed high score button:
	if (m_buttons[3].getbuttonBg().getGlobalBounds().contains(
		window->mapPixelToCoords({ event.x, event.y })))
	{
		return ClickedButton::ScoresList;
	}	
	//if the user pressed the exit button:
	if (m_buttons[4].getbuttonBg().getGlobalBounds().contains(
		window->mapPixelToCoords({ event.x, event.y })))
	{
		window->close();
		exit(EXIT_SUCCESS);
	}

	else
	{
		return ClickedButton::Invalid;
	}
}
//-------------------------------------------------------------------------------------------
void MainMenu::handleHoverOver(sf::RenderWindow* window)
{
	// ==============================================
	// ======== hovering start Game button: =========
	if (m_buttons[0].isMouseOver(*window))
		m_buttons[0].setTextColor(sf::Color::Blue);
	else
		m_buttons[0].setTextColor(sf::Color::Yellow);
	// ==============================================
	// ======== hovering over Choose Char button: =======
	if (m_buttons[1].isMouseOver(*window))
		m_buttons[1].setTextColor(sf::Color::Blue);
	else
		m_buttons[1].setTextColor(sf::Color::Yellow);
	// ==============================================
	// ======== hovering over Check Profile button: =======
	if (m_buttons[2].isMouseOver(*window))
		m_buttons[2].setTextColor(sf::Color::Blue);
	else
		m_buttons[2].setTextColor(sf::Color::Yellow);
	// ==============================================
	// ======== hovering over High Score button: =======
	if (m_buttons[3].isMouseOver(*window))
		m_buttons[3].setTextColor(sf::Color::Blue);
	else
		m_buttons[3].setTextColor(sf::Color::Yellow);

	// ======== hovering over exit button: =========
	if (m_buttons[4].isMouseOver(*window))
	{
		m_buttons[4].setTextColor(sf::Color::Red);
	}
	else
		m_buttons[4].setTextColor(sf::Color::Yellow);
	// ==============================================
}
//-------------------------------------------------------------------------------------------