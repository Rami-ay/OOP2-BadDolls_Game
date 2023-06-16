#pragma once
#include <SFML/Graphics.hpp>


// ===== consts: ==========
const int TILE_SIZE = 40;
constexpr int BOARD_WIDTH = 1450;
constexpr int BOARD_HEIGHT = 950;
const sf::Font& getGlobalFont();

// ===== enums: ==========
enum ObjectTypes
{
	wallObject = '#',
	firstPlayerObject = 'P',
	secondPlayerObject = 'p',
	enemyBearObject = 'B',
	heartObject = 'H',
	coinObject = 'C',
	batObject = 'Q',
	gunObject = 'G'
};
//    --------------
enum TextureTypes
{
	wall,
	firstPlayer,
	secondPlayer,
	enemy,
	menuBackGround,
	templeBackground,
	enemyBear,
	heart,
	coin,
	enemyBat,
	gun
};
//    --------------
enum class ClickedButton
{
	StartGame,
	ChooseCharacter,
	ProfileCheck,
	ScoresList,
	Exit,
	Login,
	Help,
	Invalid
};
//    --------------
//enum class GameObjectIndex
//{
//	firstPlayer,
//	secondPlayer,
//	Wall,
//	MAX
//};
//    --------------
enum class Direction
{
	Up,
	Down,
	Right,
	Left,
	Stay,
	Max,
};
//    --------------





////changes the objects on the boards
//void Board::handleBoard(Controller& controller, MovingObject& movingObjects)
//{
//	for (int i = 0; i < m_fixedObjects.size(); i++)
//	{
//		FixedObject* object = m_fixedObjects[i].get();
//		AllGifts* gift = dynamic_cast<AllGifts*>(object);
//
//		//checks if activated a gift
//		if (gift)
//		{
//			if (gift->getActivated())
//			{
//				gift->doGiftTask(controller, m_movingObjects);
//
//				//check if the pacman touched a heart(health object)
//				if (gift->getObject() == healthObject)
//				{
//					//add a heart if the hearts are not full
//					for (int j = m_livesObjects.size() - 1; j > -1; j--)
//					{
//						if (m_livesObjects[j].getColor() == sf::Color(100, 100, 100, 100))
//						{
//							m_livesObjects[j].setColor(sf::Color(255, 255, 255, 255));
//							break;
//						}
//
//					}
//				}
//
//				else if (gift->getObject() == iceBallObject)
//				{
//					//start the freezing clock to freeze the ghosts for 5 seconds
//					m_freezingClock.restart();
//					controller.setFreezeGhosts(true);
//				}
//				else if (gift->getObject() == giftObject)
//				{
//					//start the super clock to make the pacman super for 5 seconds
//					m_superClock.restart();
//					controller.setSuper(true);
//				}
//				else if (gift->getObject() == bombObject)
//				{
//					//if the pacman touched the bomb it will lose 2 lives
//					controller.setHealth(-2);
//
//					//to make 2 hearts half transparent
//					int x = 0;
//					while (x < 2)
//					{
//						for (size_t j = 0; j < m_livesObjects.size(); j++)
//						{
//							if (m_livesObjects[j].getColor() != sf::Color(100, 100, 100, 100))
//							{
//								m_livesObjects[j].setColor(sf::Color(100, 100, 100, 100));
//								x++;
//								break;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//	//when freezing time is 5 seconds
//	if (m_freezingClock.getElapsedTime().asSeconds() >= 5)
//	{
//		//restart the freezing time
//		m_freezingClock.restart();
//		controller.setFreezeGhosts(false);//stop the freezing(make it false)
//	}
//	//when the pacman is super for 5 seconds
//	if (m_superClock.getElapsedTime().asSeconds() >= 5 && controller.getSuper())
//	{
//		//restart the super time
//		m_superClock.restart();
//		controller.setSuper(false);//stop the super(make it false)
//	}
//
//	//handle the collision with the cake
//	for (int i = 0; i < m_fixedObjects.size(); i++)
//	{
//		FixedObject* object = m_fixedObjects[i].get();
//		Cake* cake = dynamic_cast<Cake*>(object);
//
//		//checks if took a cake
//		if (cake)
//		{
//			if (cake->getDelete())
//			{
//				m_eatenCakeCounter++;//increase the number of the eaten cakes
//				controller.setPoints(CAKE_POINTS);//add the cake points
//
//				//check if all the cakes are eaten
//				if (m_eatenCakeCounter == m_cakeCounter)
//				{
//					//if the player wins a level, add 2 points for every ghost in the level
//					controller.setPoints(GHOSTS_POINTS * getGhostsNum());
//				}
//			}
//		}
//	}
//
//	//check the key and door
//	for (int i = 0; i < m_fixedObjects.size(); i++)
//	{
//		FixedObject* object = m_fixedObjects[i].get();
//		Key* key = dynamic_cast<Key*>(object);
//
//		//checks if took a key
//		if (key)
//		{
//			if (key->getDelete())
//			{
//				controller.setPoints(KEY_POINTS);//add the points of the key
//				for (int i = 0; i < m_fixedObjects.size(); i++)
//				{
//					FixedObject* object = m_fixedObjects[i].get();
//					Door* door = dynamic_cast<Door*>(object);
//
//					//deletes a door
//					if (door)
//					{
//						door->deleteObject();
//						break;
//					}
//				}
//			}
//		}
//	}
//
//	//to handle the moving objects
//	for (size_t i = 0; i < m_movingObjects.size(); i++)
//	{
//		if (m_movingObjects[i].get()->getObject() == pacmanObject)
//		{
//			MovingObject* object = m_movingObjects[i].get();
//			Pacman* pacmanObject = dynamic_cast<Pacman*>(object);
//
//			//if the pacman is super, make it red
//			if (controller.getSuper())
//				pacmanObject->changeColor(sf::Color::Red);
//			else
//			{
//				pacmanObject->setDestroyTheDoor(false);//now the pacman cant destroy the doors
//				pacmanObject->changeColor(sf::Color(255, 255, 255, 255)); //color it to the original color
//				pacmanObject->setSpeed(sf::Vector2f(SPEED, SPEED)); //set the speed to the regular speed
//			}
//		}
//
//		//if not pacman(if ghost)
//		else
//		{
//			//if the ghosts are not freezed, color them to their original color
//			if (!controller.getFreezeGhosts())
//				m_movingObjects[i]->changeColor(sf::Color(255, 255, 255, 255));
//		}
//	}
//
//	//handle the collision with the ghosts
//	for (int i = 0; i < m_movingObjects.size(); i++)
//	{
//		MovingObject* object = m_movingObjects[i].get();
//		Ghost* ghost = dynamic_cast<Ghost*>(object);
//
//		//checks if the pacman touched a ghost
//		if (ghost)
//		{
//			//if the regular pacman touched a ghost
//			if (ghost->getTouchedPacman() && !controller.getSuper())
//			{
//				Resources::instance().playSound(touchGhost);
//				controller.setHealth(-1); //decrease the health by 1
//
//				for (size_t j = 0; j < m_movingObjects.size(); j++)
//				{
//					//return all the moving objects to their initial position
//					m_movingObjects[j].get()->setPosition(m_movingInitPos[j]);
//					ghost->setTouchPacman(false);
//				}
//
//				//make one heart half transparent
//				for (size_t j = 0; j < m_livesObjects.size(); j++)
//				{
//					if (m_livesObjects[j].getColor() != sf::Color(100, 100, 100, 100))
//					{
//						m_livesObjects[j].setColor(sf::Color(100, 100, 100, 100));
//						break;
//					}
//				}
//			}
//			else
//				ghost->setTouchPacman(false);
//		}
//		MovingObject* p = m_movingObjects[i].get();
//
//		Pacman* pacman = dynamic_cast<Pacman*>(p);
//		if (pacman)
//		{
//			if (m_cakeCounter == m_eatenCakeCounter)
//			{
//				controller.levelWon();
//				controller.setHealth(3);
//				Resources::instance().playSound(gameWon);
//			}
//		}
//	}
//
//	//erasing the objects that deleted
//	std::erase_if(m_fixedObjects, [](const auto& object) {return object->getDelete(); });
//}