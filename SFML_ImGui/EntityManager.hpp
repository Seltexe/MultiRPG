#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <vector>
#include <memory>

class EntityManager {
public:
    template<typename T, typename... Args>
    static T& CreateEntity(Args&&... args) {
        static_assert(std::is_base_of<Entity, T>::value,
            "T must inherit from Entity");
        auto entity = std::make_unique<T>(std::forward<Args>(args)...);
        auto& ref = *entity;
        m_entities.push_back(std::move(entity));
        return ref;
    }

    static void UpdateAll(sf::Time dt) {
        for (auto& entity : m_entities) {
            entity->Update(dt);
        }
    }

	static void DrawAll() {
		for (auto& entity : m_entities) {
			entity->Draw();
		}
	}

private:
    inline static std::vector<std::unique_ptr<Entity>> m_entities;
};