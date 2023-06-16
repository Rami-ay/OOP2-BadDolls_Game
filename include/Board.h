#pragma once
#include "Resources.h"
#include "io.h"
#include "GameObject.h"
#include "StaticObject.h"
#include "Wall.h"
#include "Player.h"
#include "FirstPlayer.h"
#include "SecondPlayer.h"
#include "MovingObject.h"
#include "Controller.h"
#include <vector>
#include <memory>
#include <exception>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "CollisionHandling.h"
#include "EnemyBear.h"
#include "Heart.h"
#include <iostream>
#include "Coin.h"
#include "EnemyBat.h"
#include "Gun.h"





class controller;


class Board
{

public:
	//constructor:
	Board(const sf::RenderWindow*, const int);

	void draw(Controller&);
	void drawInfo(Controller&);
	void updatePlayers(sf::Time);
	void directionPlayers(sf::Keyboard::Key first, sf::Keyboard::Key second);
	void collision();
	bool collide(GameObject& a, GameObject& b);
	void handleBoard();
	sf::Vector2f boardToBox2D(sf::Vector2f objectPosition, sf::Vector2f levelSize);
	sf::Vector2f box2DtoBoard(std::pair<float, float> box2DPosition, sf::Vector2f levelSize);

	//templated function:
	//================================================================
	template <typename FwdIt, typename Fn>
	void for_each_pair(FwdIt begin, FwdIt end, Fn fn)
	{
		for (; begin != end; ++begin)
			for (auto second = begin + 1; second != end; ++second)
				fn(*begin, *second);

	}
	//================================================================

private:
	sf::RectangleShape m_board;
	sf::Vector2f m_levelSize;
	sf::Vector2f m_levelPosition;
	sf::Sprite m_backGround;

	//box2d world for the game physics:
	std::unique_ptr<b2World> m_gameWorld;

	std::vector<std::unique_ptr<MovingObject>> m_movingObjects;
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
	std::vector<sf::Sprite> m_livesObjects;
	void makeObject(const ObjectTypes&, const sf::Vector2f&, std::unique_ptr<b2World>& world);

	//Board Helping Functions:
	float Xposition(const int) const;
	float Yposition(const int) const;

	static std::unique_ptr<MovingObject> createMovingObject(ObjectTypes type,
		const sf::Vector2f& position,
		const std::vector<sf::Texture>& textures, sf::Vector2f b2dpos, std::unique_ptr<b2World>& world);

	static std::unique_ptr<StaticObject> createStaticObject(ObjectTypes type,
		const sf::Vector2f& position,
		const std::vector<sf::Texture>& textures);
};