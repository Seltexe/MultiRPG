#pragma once
#include "tools.hpp"
#include "Entity.hpp"
#include "Window.hpp"

class Player : public Entity
{
public:
	Player();
	~Player() = default;

	void Update(sf::Time dt) override;
	void Draw() override;

private:
	sf::RectangleShape m_shape;

	float m_maxSpeed;
	float m_friction;
	float m_gravity;
	bool m_isGrounded;
	float m_jumpStrength;
};