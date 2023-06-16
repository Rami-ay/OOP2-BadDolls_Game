#pragma once


// --- includes --- 
#include <SFML/Graphics.hpp>
#include "StartMenu.h"
#include "MainMenu.h"
#include <utility>
#include "io.h"
#include "FirstPlayer.h"


class Board;


class Controller
{

public:
    Controller();
    ~Controller() {};
    void run();
    sf::RenderWindow* getWindow() const;
    void startGame();
    void handleEvent(sf::Event& event1, sf::Event& event2, Board& gameBoard);

private:
    //window:
    sf::RenderWindow* m_window;
    sf::Clock gameClock = sf::Clock();

    //start menu:
    StartMenu m_startMenu = StartMenu();
    //Main Menu:
    MainMenu m_mainMenu = MainMenu();

    //the desired operation in Main Menu:
    ClickedButton m_mainMenu_clickedButton;
    //the desired operation in Start Menu:
    ClickedButton m_startMenu_clickedButton;

    //first player's name:
    std::string m_player1Name;
    int m_currentLevel;

    //Helping functions:
    void isPlayerExist(std::string playersName);
    void createPlayerProfile(std::string playerName);
};