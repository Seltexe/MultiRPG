#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	~Entity() = default;

	virtual void Update(sf::Time dt) = 0;
	virtual void Draw() = 0;

protected:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
};