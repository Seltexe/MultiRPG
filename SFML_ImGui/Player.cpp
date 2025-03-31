#include "pch.h"
#include "Player.hpp"

Player::Player()
    : m_shape(sf::Vector2f(50, 50))
{
    m_position = sf::Vector2f(100, 100);
    m_velocity = sf::Vector2f(0, 0);
    m_acceleration = sf::Vector2f(0, 0);
    m_maxSpeed = 1000.0f; // Augmentez la vitesse maximale
    m_friction = 0.95f;   // Réduisez la friction

    m_shape.setPosition(m_position);
    m_shape.setFillColor(sf::Color::Green);
}

void Player::Update(sf::Time dt)
{
    float deltaTime = tools::getDeltaTime(dt);

    m_acceleration = sf::Vector2f(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_acceleration.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_acceleration.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_acceleration.x = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_acceleration.x = 1;
    }

    if (m_acceleration != sf::Vector2f(0, 0))
    {
        m_acceleration = tools::normalizef(m_acceleration);
    }

    m_velocity += m_acceleration * m_maxSpeed * deltaTime;

    // Appliquer la friction
    m_velocity *= m_friction;

    // Limiter la vitesse maximale
    if (tools::getMagnitude(m_velocity) > m_maxSpeed)
    {
        m_velocity = tools::normalizef(m_velocity) * m_maxSpeed;
    }

    m_position += m_velocity * deltaTime;

    m_shape.setPosition(m_position);
}

void Player::Draw()
{
    Window::draw(m_shape);
}
