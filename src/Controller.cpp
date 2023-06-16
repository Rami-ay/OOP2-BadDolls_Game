#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Resources.h"

//default Controller constructor:
Controller::Controller():m_currentLevel(0), m_mainMenu_clickedButton(ClickedButton::Invalid)
{
	m_window = new sf::RenderWindow(sf::VideoMode(BOARD_WIDTH, BOARD_HEIGHT), "Bad Dolls");
	m_startMenu.setStartMenu();
	m_mainMenu.setMainMenu();
}
//-------------------------------------------------------------------------------------------
//function that runs the game from start to end:
void Controller::run()
{
	m_window->setFramerateLimit(60);
	//display the start menu and store the players name:
	if (m_startMenu.displayMenu(m_window) == ClickedButton::Login)
	{
		//get the first player's name:
		m_player1Name = m_startMenu.getPlayerName();
		
		//check if the player exist, if not create a profile for him:
		isPlayerExist(m_player1Name);
	}
	//display the MainMenu and start if the player clicks start game:
	if (m_mainMenu.displayMenu(m_window) == ClickedButton::StartGame)
		startGame();


}
//-------------------------------------------------------------------------------------------
void Controller::startGame()
{
	srand(static_cast<unsigned>(time(nullptr)));

	sf::Event event1;
	sf::Event event2;
	
	Board gameBoard(m_window, m_currentLevel);
	while (m_window->isOpen())
	{	
		//clear the window:
		m_window->clear(sf::Color::Black);
		//draw the board:
		gameBoard.draw(*this);
		//display:
		m_window->display();


		event2.key.code = sf::Keyboard::Space;
		event1.key.code = sf::Keyboard::H;

		while (m_window->pollEvent(event1))
		{
			handleEvent(event1, event2, gameBoard);
		}
		
		const auto delta = gameClock.restart();
		//get the new position
		gameBoard.updatePlayers(delta);
	
	}
}
//-------------------------------------------------------------------------------------------
//function that returs the window:
sf::RenderWindow* Controller::getWindow() const
{
	return m_window;
}
//-------------------------------------------------------------------------------------------
//function that handle the events of moving the two players:
void Controller::handleEvent(sf::Event& event1, sf::Event& event2, Board& gameBoard)
{
	if (event1.type == sf::Event::Closed || event2.type == sf::Event::Closed)
	{
		m_window->close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		event1.key.code = sf::Keyboard::Up;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		event1.key.code = sf::Keyboard::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		event1.key.code = sf::Keyboard::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		event1.key.code = sf::Keyboard::Down;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		event2.key.code = sf::Keyboard::W;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		event2.key.code = sf::Keyboard::D;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		event2.key.code = sf::Keyboard::A;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		event2.key.code = sf::Keyboard::S;
	}

	gameBoard.directionPlayers(event1.key.code, event2.key.code);
}
//-------------------------------------------------------------------------------------------
//This function gets the players name and check if it exists in 
// resourses/textFiles/PlayersNames.txt,if the player does not exist it adds the player name 
//and create default info of him in resourses/textFiles/PlayersDetails.txt
void Controller::isPlayerExist(std::string playerName)
{
	//get the names found in the PlayersNames.txt:
	auto& currentPlayers = Resources::instance().getPlayers();
	//now check if the given name is the currentPlayers:
	bool found = false;
	for (const std::string& player : currentPlayers)
	{
		if (player == playerName)
		{
			found = true;
			break;
		}
	}
	// if the given PlayerName is not found:
	if (!found)
	{
		//call the function that builds default data of player:
		createPlayerProfile(playerName);
	}
	else
	{
		//Nothing needed to be done , player has his own data!!
	}

}

//this function gets playerName that is not found in the recourses
//and add it's name and a default info about a new player:
void Controller::createPlayerProfile(std::string playerName)
{
	// Add the new player name to the PlayersName.txt file
	std::ofstream playersNamesFile("..\\..\\..\\resources\\textFiles\\PlayersNames.txt");
	if (playersNamesFile.is_open())
	{
		playersNamesFile << playerName;
		playersNamesFile.close();
	}
	else
	{
		// Handle the case where the file couldn't be opened for writing
		std::cerr << "Error: Unable to open PlayersNames.txt for writing." << std::endl;
		return; // or throw an exception, depending on your error handling strategy
	}

	// Create the new player profile to the PlayersDetails.txt file
	std::ofstream playerDetailsFile("..\\..\\..\\resources\\textFiles\\PlayersDetails.txt");
	if (playerDetailsFile.is_open())
	{
		playerDetailsFile << "Name: " << playerName << "\n" <<
			"Level: 1\n" << "Score: 0\n" << "Character: Default\n" << "Map: FirstMap\n"
			<< "Kills: 0\n" << "Coins: 0\n";
		playerDetailsFile.close();
	}

	else
	{
		// Handle the case where the file couldn't be opened for writing
		std::cerr << "Error: Unable to open PlayersDetails.txt for writing." << std::endl;
		return; // or throw an exception, depending on your error handling strategy
	}
}