#include "EnemyBat.h"



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
EnemyBat::EnemyBat(const sf::Sprite& sprite) :Enemy(sprite),
m_animation(Resources::instance().animationData(Resources::EnemyBat), Direction::Right, getSprite(), int(TextureTypes::enemyBat)) 
{
    setHealth(150);
}

void EnemyBat::update(sf::Time delta)
{
    if (m_dir == Direction::Stay)
    {
        return;
    }

    getSprite().move(toVector(m_dir) * delta.asSeconds() * FirstPlayerSpeed);
    m_dir = Direction::Stay;
    m_animation.update(delta);
}

void EnemyBat::direction(sf::Keyboard::Key key)
{
    if (auto dir = toDirection(key))
    {
        m_dir = *dir;
        m_animation.direction(*dir);
    }
}
