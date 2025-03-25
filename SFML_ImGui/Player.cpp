#include "pch.h"
#include "Player.hpp"

Player::Player()
    : m_shape(sf::Vector2f(50, 50))
{
    m_position = sf::Vector2f(100, 100);
    m_velocity = sf::Vector2f(0, 0);
    m_acceleration = sf::Vector2f(0, 0);
    m_maxSpeed = 8000.0f;
    m_friction = 0.98f; // Reduced friction for more sliding
    m_gravity = 1000.f; // Increased gravity for more dynamic jumps
    m_jumpStrength = 500.0f; // Added jump strength
    m_isGrounded = false;

    m_shape.setPosition(m_position);
    m_shape.setFillColor(sf::Color::Green);
}

void Player::Update(sf::Time dt)
{
    float deltaTime = tools::getDeltaTime(dt);

    m_acceleration = sf::Vector2f(0, 0);

    if (ButtonManager::isKeyPressed(sf::Keyboard::W) && m_isGrounded)
    {
        m_velocity.y = -m_jumpStrength; // Use jump strength
        m_isGrounded = false;
    }
    if (ButtonManager::isKeyPressed(sf::Keyboard::A))
    {
        m_acceleration.x = -1;
    }
    if (ButtonManager::isKeyPressed(sf::Keyboard::D))
    {
        m_acceleration.x = 1;
    }

    if (m_acceleration != sf::Vector2f(0, 0))
    {
        m_acceleration = tools::normalizef(m_acceleration);
    }

    m_velocity += m_acceleration * m_maxSpeed * deltaTime;

    m_velocity.y += m_gravity * deltaTime;

    m_velocity.x *= m_friction;

    if (tools::getMagnitude(m_velocity) > m_maxSpeed)
    {
        m_velocity = tools::normalizef(m_velocity) * m_maxSpeed;
    }

    m_position += m_velocity * deltaTime;

    if (m_position.y > 600.f)
    {
        m_position.y = 600.f;
        m_isGrounded = true;
    }

    m_shape.setPosition(m_position);
}

void Player::Draw()
{
    Window::draw(m_shape);
}
