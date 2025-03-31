#pragma once
#include "tools.hpp"
#include "Entity.hpp"
#include "Window.hpp"

class Consumable : public Entity
{
public:
	Consumable();
	~Consumable() = default;

	void Update(sf::Time dt) override;
	void Draw() override;

private:
	sf::CircleShape m_shape;

	std::string m_name;
};
