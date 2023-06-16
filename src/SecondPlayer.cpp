#include "SecondPlayer.h"
#include"FirstPlayer.h"
#include <optional>
#include "Direction.h"

constexpr auto SecondPlayerSpeed = 150.f;

namespace
{
    std::optional<Direction> toDirection(sf::Keyboard::Key key)
    {
        switch (key)
        {
        case sf::Keyboard::A:
            return Direction::Left;
        case sf::Keyboard::D:
            return Direction::Right;
        case sf::Keyboard::W:
            return Direction::Up;
        case sf::Keyboard::S:
            return Direction::Down;
        case sf::Keyboard::H:
            return Direction::Stay;
        }
        return {};
    }
}

SecondPlayer::SecondPlayer(const sf::Sprite& sprite) :Player(sprite),
m_animation(Resources::instance().animationData(Resources::SecondPlayer), Direction::Right, getSprite(), int(TextureTypes::secondPlayer))
{
    setHealth(100);
}


void SecondPlayer::update(sf::Time delta)
{
    if (m_dir == Direction::Stay)
    {
        return;
    }

    getSprite().move(toVector(m_dir) * delta.asSeconds() * SecondPlayerSpeed);
    m_dir = Direction::Stay;
    m_animation.update(delta);
}

void SecondPlayer::direction(sf::Keyboard::Key key)
{
    if (auto dir = toDirection(key))
    {
        m_dir = *dir;
        m_animation.direction(*dir);
    }
}

void SecondPlayer::addHealth(int h)
{
    if (h + getHealth() > 100)
        setHealth(100);
    else
        setHealth(h + getHealth());
}
