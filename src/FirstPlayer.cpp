#include"FirstPlayer.h"
#include <optional>
#include "Direction.h"

constexpr auto FirstPlayerSpeed = 150.f;
namespace
{
    std::optional<Direction> toDirection(sf::Keyboard::Key key)
    {
        switch (key)
        {
        case sf::Keyboard::Left:
            return Direction::Left;
        case sf::Keyboard::Right:
            return Direction::Right;
        case sf::Keyboard::Up:
            return Direction::Up;
        case sf::Keyboard::Down:
            return Direction::Down;
        case sf::Keyboard::Space:
            return Direction::Stay;
        }
        return {};
    }
}
//-------------------------------------------------------------------------------------------
FirstPlayer::FirstPlayer(const sf::Sprite& sprite, sf::Vector2f b2dPos, std::unique_ptr<b2World>& world) :
    Player(sprite),m_animation(Resources::instance().animationData(Resources::FirstPlayer), Direction::Right, getSprite(),
int(TextureTypes::firstPlayer))
{
    //set the players health:
    setHealth(120);

    // Create a dynamic body for Box2D
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    // Set position
    bodyDef.position.Set(b2dPos.x, b2dPos.y);
    m_b2dBody = world->CreateBody(&bodyDef);

    // Set the dimensions of the player shape
    float playerWidth = 32.0f / TILE_SIZE;  // Convert pixels to Box2D units
    float playerHeight = 32.0f / TILE_SIZE;

    // Create the shape
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(playerWidth / 2.0f, playerHeight / 2.0f);  // Half-width and half-height

    // Set fixture properties
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    m_b2dBody->CreateFixture(&fixtureDef);
    
    
}
//-------------------------------------------------------------------------------------------
void FirstPlayer::update(sf::Time delta)
{
    if (m_dir == Direction::Stay)
    {
        return;
    }

    getSprite().move(toVector(m_dir) * delta.asSeconds() * FirstPlayerSpeed);
    m_dir = Direction::Stay;
    m_animation.update(delta);
}
//-------------------------------------------------------------------------------------------
void FirstPlayer::direction(sf::Keyboard::Key key)
{
    if (auto dir = toDirection(key))
    {
        m_dir = *dir;
        m_animation.direction(*dir);
    }
}
//-------------------------------------------------------------------------------------------
void FirstPlayer::addHealth(int h)
{
    if (h + getHealth() > 120)
        setHealth(120);
    else
        setHealth(h + getHealth());
}
//-------------------------------------------------------------------------------------------
