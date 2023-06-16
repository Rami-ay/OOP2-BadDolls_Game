#include "StartMenu.h"


void StartMenu::setStartMenu()
{
	auto& texture = Resources::instance().getTextures()[menuBackGround];
	m_bgSprite = sf::Sprite(texture);

	//setting the User Login in button:
	m_buttons.push_back(Button("User Login", { 0.2 * BOARD_WIDTH , 0.12 * BOARD_HEIGHT }, 0.05 * BOARD_HEIGHT,
		sf::Color::Transparent, sf::Color::Yellow, { 0.4 * BOARD_WIDTH , 0.2 * BOARD_HEIGHT }, getGlobalFont()));

	//setting the help button :
	m_buttons.push_back(Button("Help", { 0.2 * BOARD_WIDTH , 0.12 * BOARD_HEIGHT }, 0.05 * BOARD_HEIGHT,
		sf::Color::Transparent, sf::Color::Yellow, { 0.4 * BOARD_WIDTH , 0.44 * BOARD_HEIGHT }, getGlobalFont()));


	//setting the exit button:
	m_buttons.push_back(Button("Exit Game", { 0.2 * BOARD_WIDTH, 0.12 * BOARD_HEIGHT }, 0.05 * BOARD_HEIGHT,
		sf::Color::Transparent, sf::Color::Yellow, { 0.4 * BOARD_WIDTH , 0.68 * BOARD_HEIGHT }, getGlobalFont()));

	//setting the log in text box :
	setupNameInput();

	//setting the back button for the login menu:
	m_backButton = Button("Back", { 0.2 * BOARD_WIDTH, 0.12 * BOARD_HEIGHT }, 0.05 * BOARD_HEIGHT,
		sf::Color::Transparent, sf::Color::Yellow, { 0.4 * BOARD_WIDTH , 0.68 * BOARD_HEIGHT }, getGlobalFont());
}
//-------------------------------------------------------------------------------------------
ClickedButton StartMenu::displayMenu(sf::RenderWindow* window)
{
	ClickedButton clicked = ClickedButton::Invalid;
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
				if (clicked == ClickedButton::Login)
					return ClickedButton::Login;
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
ClickedButton StartMenu::handleClick(const sf::Event::MouseButtonEvent& event, sf::RenderWindow* window)
{
	//if the user pressed the login button:
	if (m_buttons[0].getbuttonBg().getGlobalBounds().contains(
		window->mapPixelToCoords({ event.x, event.y })))
	{
		handleTextInput(window);
		return ClickedButton::Login;
	}
	//if the user pressed the help button button:
	if (m_buttons[1].getbuttonBg().getGlobalBounds().contains(
		window->mapPixelToCoords({ event.x, event.y })))
	{
		m_helpWindow.help_run();
		return ClickedButton::Help;

	}
	//if the user pressed the check profile button:
	if (m_buttons[2].getbuttonBg().getGlobalBounds().contains(
		window->mapPixelToCoords({ event.x, event.y })))
	{
		return ClickedButton::ProfileCheck;
	}
	//if the user pressed the exit button:
	if (m_buttons[3].getbuttonBg().getGlobalBounds().contains(
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
void StartMenu::handleHoverOver(sf::RenderWindow* window) 
{
	 //==============================================
	 //======== hovering over login button: =========
	if (m_buttons[0].isMouseOver(*window))
		m_buttons[0].setTextColor(sf::Color::Blue);
	else
		m_buttons[0].setTextColor(sf::Color::Yellow);
	// ==============================================
	// ======== hovering over help button: =========
	if (m_buttons[1].isMouseOver(*window))
		m_buttons[1].setTextColor(sf::Color::Blue);
	else
		m_buttons[1].setTextColor(sf::Color::Yellow);
	// ==============================================
	// ======== hovering over exit button: =========
	if (m_buttons[2].isMouseOver(*window))
		m_buttons[2].setTextColor(sf::Color::Red);
	else
		m_buttons[2].setTextColor(sf::Color::Yellow);
	// ==============================================
}
//-------------------------------------------------------------------------------------------
void StartMenu::handleTextInput(sf::RenderWindow* window)
{
	std::string enteredName;
	sf::Event event;

	// Cursor properties
	sf::RectangleShape cursor;
	cursor.setSize(sf::Vector2f(2.0f, m_playerName.getCharacterSize()));
	cursor.setFillColor(sf::Color::Black);
	bool showCursor = true;
	sf::Clock cursorTimer;

	// Instructions text
	sf::Text instructions;
	instructions.setString("Enter your name:");
	instructions.setFont(getGlobalFont());
	instructions.setCharacterSize(24);
	instructions.setFillColor(sf::Color(200, 200, 255));
	instructions.setPosition(m_nameBackGround.getPosition().x, m_nameBackGround.getPosition().y - 0.05 * BOARD_HEIGHT);

	// Light attractive color for the text box
	sf::Color textBoxColor(200, 200, 255); 

	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				exit(EXIT_SUCCESS);
			}

			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == '\b' && !enteredName.empty())
				{
					// Handle backspace
					enteredName.pop_back();
				}
				else if (std::isalnum(event.text.unicode) && enteredName.length() < 15)
				{
					// Append entered alphanumeric character
					enteredName += static_cast<char>(event.text.unicode);
				}

				if (event.text.unicode == '\r' || event.text.unicode == '\n')
				{
					// User pressed Enter, store the entered name and return
					m_finalPlayerName = enteredName;
					return;
				}
			}
		}

		// Clear the window
		window->clear();

		// Draw the background sprite
		window->draw(m_bgSprite);

		// Draw the instructions text
		window->draw(instructions);

		// Draw the name input rectangle
		m_nameBackGround.setFillColor(textBoxColor); // Set the fill color
		window->draw(m_nameBackGround);

		// Update the entered text
		m_playerName.setString(enteredName);

		// Draw the entered name text
		window->draw(m_playerName);

		// Draw the back button:
		m_backButton.drawTo(*window);

		// Draw the cursor
		if (cursorTimer.getElapsedTime().asSeconds() >= 0.5f)
		{
			showCursor = !showCursor;
			cursorTimer.restart();
		}
		if (showCursor)
		{
			cursor.setPosition(m_playerName.findCharacterPos(enteredName.size()));
			window->draw(cursor);
		}

		// Display the updated window
		window->display();
	}
}
//-------------------------------------------------------------------------------------------
void StartMenu::setupNameInput()
{
	// Name input box
	m_nameBackGround.setSize(sf::Vector2f(0.2 * BOARD_WIDTH, 0.06 * BOARD_HEIGHT));
	m_nameBackGround.setFillColor(sf::Color::Blue);
	m_nameBackGround.setOutlineColor(sf::Color::Black);
	m_nameBackGround.setOutlineThickness(4.0f);
	m_nameBackGround.setPosition({ 0.4 * BOARD_WIDTH , 0.44 * BOARD_HEIGHT });

	// Player name text
	m_playerName.setString("");
	m_playerName.setFont(getGlobalFont());
	m_playerName.setCharacterSize(24);
	m_playerName.setFillColor(sf::Color::Black);
	m_playerName.setPosition(m_nameBackGround.getPosition().x + (m_nameBackGround.getGlobalBounds().width / 10),
		m_nameBackGround.getPosition().y + (m_nameBackGround.getGlobalBounds().height / 4));
}
//-------------------------------------------------------------------------------------------
std::string StartMenu::getPlayerName() const
{
	return m_finalPlayerName;
}