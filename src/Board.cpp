#include "Board.h"


//board constructor:
Board::Board(const sf::RenderWindow* window, const int lvl)
{
	m_backGround.setTexture(Resources::instance().getTextures()[templeBackground]);
	//build the level
	auto map = Resources::instance().buildMap(lvl);
	int numOfCols = (int)map[0].size();
	int numOfRows = (int)map.size();

	m_levelSize = sf::Vector2f((float)numOfCols * TILE_SIZE, (float)numOfRows * TILE_SIZE);

	m_levelPosition = sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f);

	m_board = sf::RectangleShape(m_levelSize);

	m_board.setFillColor(sf::Color(255, 255, 255, 128));

	m_board.setOrigin(m_levelSize / 2.f);

	m_board.setPosition(m_levelPosition);

	//init the gameworld 
	b2Vec2 gravity(0.0f, -10.0f);
	m_gameWorld = std::make_unique<b2World>(gravity);

	for (int row = 0; row < numOfRows; row++)
	{
		for (int col = 0; col < numOfCols; col++)
		{
			char tile = map[row][col];

			makeObject((ObjectTypes)tile, sf::Vector2f(Xposition(col), Yposition(row)), m_gameWorld);

		}
	}
	

}
//-------------------------------------------------------------------------------------------
//function that draws the board objects on the controllers window:
void Board::draw(Controller& controller)
{
	auto window = controller.getWindow();

	window->draw(m_backGround);
	drawInfo(controller);
	window->draw(m_board);


	for (auto& object : m_movingObjects)
	{
		object->draw(window);
	}
	for (auto& object : m_movingObjects)
	{
		Player* player = dynamic_cast<Player*>(object.get());
		if (player)
		{
			for (int i = 0; i < player->getGunCount(); i++)
			{
				Gun gun = player->getGun(i);  
				gun.setPosition(sf::Vector2f(player->getPosition().x + 10,player->getPosition().y + 20));
				gun.draw(window);
			}
		}
	}



	for (auto& object : m_staticObjects)
	{
		object->draw(window);
	}

}
void Board::drawInfo(Controller& controller)
{
	auto window = controller.getWindow();
	auto font = Resources::instance().getFont();

	int firstPlayerPoints = 0;
	int firstPlayerHealth = 0;
	int firstPlayerCoins = 0;

	int secondPlayerPoints = 0;
	int secondPlayerHealth = 0;
	int secondPlayerCoins = 0;

	for (auto& object : m_movingObjects)
	{
		MovingObject* ob = object.get();
		FirstPlayer* firstPlayerObject = dynamic_cast<FirstPlayer*>(ob);
		if (firstPlayerObject)
		{
			firstPlayerPoints = firstPlayerObject->getPoints();
			firstPlayerHealth = firstPlayerObject->getHealth();
			firstPlayerCoins = firstPlayerObject->getCoins();
		}
		else
		{
			MovingObject* ob = object.get();
			SecondPlayer* secondPlayerObject = dynamic_cast<SecondPlayer*>(ob);
			if (secondPlayerObject)
			{
				secondPlayerPoints = secondPlayerObject->getPoints();
				secondPlayerHealth = secondPlayerObject->getHealth();
				secondPlayerCoins = secondPlayerObject->getCoins();
			}
		}
	}

	std::string firstPointsString = std::to_string(firstPlayerPoints);
	std::string firstHealthString = std::to_string(firstPlayerHealth);
	std::string firstCoinsString = std::to_string(firstPlayerCoins);

	std::string secondPointsString = std::to_string(secondPlayerPoints);
	std::string secondHealthString = std::to_string(secondPlayerHealth);
	std::string secondCoinsString = std::to_string(secondPlayerCoins);

	sf::RectangleShape bar;
	bar.setSize(sf::Vector2f(1400.f, 40.f));
	bar.setFillColor(sf::Color(255, 255, 255, 170));
	bar.setOutlineColor(sf::Color::Black);
	bar.setOutlineThickness(2);
	bar.setOrigin(bar.getGlobalBounds().width / 2.0f, bar.getGlobalBounds().height / 2.0f);
	bar.setPosition(window->getSize().x / 2.0f, m_board.getGlobalBounds().top - 25);


	sf::Text firstCoinsText;
	firstCoinsText.setFont(font);
	firstCoinsText.setString("Player1 coins: " + firstCoinsString);
	firstCoinsText.setCharacterSize(30);
	firstCoinsText.setFillColor(sf::Color(100, 60, 100, 255));
	firstCoinsText.setOutlineThickness(1);
	firstCoinsText.setPosition(300, bar.getGlobalBounds().top + 5);

	sf::Text firstHealthText;
	firstHealthText.setFont(font);
	firstHealthText.setString("Player1 health: " + firstHealthString);
	firstHealthText.setCharacterSize(30);
	firstHealthText.setFillColor(sf::Color(100, 60, 100, 255));
	firstHealthText.setOutlineThickness(1);
	firstHealthText.setPosition(700, bar.getGlobalBounds().top + 5);

	window->draw(bar);
	window->draw(firstCoinsText);
	window->draw(firstHealthText);
	
}
//-------------------------------------------------------------------------------------------
//function that updates the players movements and call the collesion handling:
void Board::updatePlayers(sf::Time delta)
{
	for (auto& object : m_movingObjects)
	{
		MovingObject* ob = object.get();
		Player* player = dynamic_cast<Player*>(ob);
		if(player)
		{
			object->setPrevPosition(object->getPosition());
			object.get()->update(delta);
		}
		
		collision();
	}

	for (auto& object : m_staticObjects)
	{
		StaticObject* ob = object.get();
		Heart* heart = dynamic_cast<Heart*>(ob);
		if (heart)
		{
			heart->update(delta);
		}
		else
		{
			StaticObject* ob = object.get();
			Coin* coin = dynamic_cast<Coin*>(ob);
			if (coin)
			{
				coin->update(delta);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------
//function that update the desired direction of each player:
void Board::directionPlayers(sf::Keyboard::Key first, sf::Keyboard::Key second)
{
	int count = 0;
	for (auto& object : m_movingObjects)
	{

		MovingObject* ob = object.get();

		FirstPlayer* firstPlayerObject = dynamic_cast<FirstPlayer*>(ob);
		if (firstPlayerObject)
		{
			firstPlayerObject->direction(first);
			firstPlayerObject->changeGunsDirection(first);
		}

		SecondPlayer* secondPlayerObject = dynamic_cast<SecondPlayer*>(ob);
		if (secondPlayerObject)
		{
			secondPlayerObject->direction(second);
		}
	}
}
//-------------------------------------------------------------------------------------------
// function that check the collesion between all the objects in the board:
void Board::collision()
{
	// Check collisions between moving objects and static objects:
	for (const auto& movingObject : m_movingObjects)
	{
		for (const auto& staticObject : m_staticObjects)
		{
			if (collide(*movingObject, *staticObject))
			{
				processCollision(*movingObject, *staticObject);
			}
		}
	}

	// Check collisions between moving objects:
	for (const auto& movingObject1 : m_movingObjects)
	{
		for (const auto& movingObject2 : m_movingObjects)
		{
			if (movingObject1 != movingObject2 && collide(*movingObject1, *movingObject2))
			{
				processCollision(*movingObject1, *movingObject2);
			}
		}
	}
	handleBoard();
}
//-------------------------------------------------------------------------------------------
//check if two objects intersects:
bool Board::collide(GameObject& a, GameObject& b)
{
	return a.getSprite().getGlobalBounds().intersects(b.getSprite().getGlobalBounds());
}
void Board::handleBoard()
{
	std::erase_if(m_staticObjects, [](const auto& object) {return object->getDelete(); });
	std::erase_if(m_movingObjects, [](const auto& object) {return object->isDead(); });

}
//-------------------------------------------------------------------------------------------
//function that creates the moving objects:
std::unique_ptr<MovingObject> Board::createMovingObject(ObjectTypes type,
	const sf::Vector2f& position,
	const std::vector<sf::Texture>& textures, sf::Vector2f b2dpos, std::unique_ptr<b2World>& world)
{	
	auto sprite = sf::Sprite();
	sprite.setPosition(position);
	switch (type)
	{
		//first player:
	case ObjectTypes::firstPlayerObject:
		sprite.setTexture(textures[firstPlayer]);
		return std::make_unique<FirstPlayer>(sprite, b2dpos, world);
		//second player:
	case ObjectTypes::secondPlayerObject:
		sprite.setTexture(textures[secondPlayer]);
		return std::make_unique<SecondPlayer>(sprite);
		//bear enemy object:
	case ObjectTypes::enemyBearObject:
		sprite.setTexture(textures[enemyBear]);
		return std::make_unique<EnemyBear>(sprite);
		//bat enemy object
	case ObjectTypes::batObject:
		sprite.setTexture(textures[enemyBat]);
		return std::make_unique<EnemyBat>(sprite);
	}
	return nullptr;
}
//-------------------------------------------------------------------------------------------
//function that creates the static objects:
std::unique_ptr<StaticObject> Board::createStaticObject(ObjectTypes type,
	const sf::Vector2f& position,
	const std::vector<sf::Texture>& textures)
{
	auto sprite = sf::Sprite();
	sprite.setPosition(position);

	switch (type)
	{
	case ObjectTypes::wallObject:
		sprite.setTexture(textures[wall]);
		return std::make_unique<Wall>(sprite);
	case ObjectTypes::heartObject:
		sprite.setTexture(textures[heart]);
		return std::make_unique<Heart>(sprite);
	case ObjectTypes::coinObject:
		sprite.setTexture(textures[coin]);
		return std::make_unique<Coin>(sprite);
	case ObjectTypes::gunObject:
		sprite.setTexture(textures[gun]);
		return std::make_unique<Gun>(sprite);
	}

	return nullptr;
}
//-------------------------------------------------------------------------------------------
//function that makes  moving and static objects and store them in vectors:
void Board::makeObject(const ObjectTypes& type, const sf::Vector2f& position, std::unique_ptr<b2World>& world)
{
	sf::Vector2f b2dPos = boardToBox2D(position, m_levelSize);
	auto& textures = Resources::instance().getTextures();
	std::unique_ptr<StaticObject> staticObjects = createStaticObject(type, position, textures);
	if (staticObjects)
	{
		m_staticObjects.push_back(std::move(staticObjects));

		return;
	}

	std::unique_ptr<MovingObject> movingObjects = createMovingObject(type, position, textures,b2dPos, world);

	if (movingObjects)
	{
		m_movingObjects.push_back(std::move(movingObjects));
		//m_movingInitPos.push_back(position);
		return;
	}
}
//-------------------------------------------------------------------------------------------
//according to the board
float Board::Xposition(const int number) const
{
	return float((m_levelPosition.x - m_levelSize.x / 2) + number * TILE_SIZE);
}
//-------------------------------------------------------------------------------------------
//according to the board
float Board::Yposition(const int number) const
{
	return float((m_levelPosition.y - m_levelSize.y / 2) + number * TILE_SIZE);
}
//-------------------------------------------------------------------------------------------
//Function that converts board coordinates to box2d coordinates:
sf::Vector2f Board::boardToBox2D(sf::Vector2f objectPosition,sf::Vector2f levelSize)
{
	// Assuming m_levelSize is the size of the game board in tiles
	float boardWidth = m_levelSize.x * TILE_SIZE;
	float boardHeight = m_levelSize.y * TILE_SIZE;

	// Calculate the center of the board
	float boardCenterX = boardWidth / 2;
	float boardCenterY = boardHeight / 2;

	// Calculate the scaling factor for converting game coordinates to Box2D coordinates
	float scalingFactor = 1.0f / TILE_SIZE;

	// Calculate the Box2D position based on game position
	float box2DX = (objectPosition.x - boardCenterX) * scalingFactor;
	float box2DY = (objectPosition.y - boardCenterY) * scalingFactor;

	return sf::Vector2f(box2DX, box2DY);
}
//-------------------------------------------------------------------------------------------
// Function that converts Box2D coordinates to board coordinates
sf::Vector2f Board::box2DtoBoard(std::pair<float, float> box2DPosition,sf::Vector2f levelSize)
{
	// Assuming m_levelSize is the size of the game board in tiles
	int boardWidth = levelSize.x * TILE_SIZE;
	int boardHeight = levelSize.y * TILE_SIZE;

	// Calculate the center of the board
	int boardCenterX = boardWidth / 2;
	int boardCenterY = boardHeight / 2;

	// Calculate the scaling factor for converting Box2D coordinates to game coordinates
	float scalingFactor = TILE_SIZE;

	// Calculate the game position based on Box2D position
	float boardX = (box2DPosition.first / scalingFactor) + boardCenterX;
	float boardY = (box2DPosition.second / scalingFactor) + boardCenterY;

	return sf::Vector2f(boardX, boardY);
}


