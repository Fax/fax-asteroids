#include "entt/entt.hpp"
#include "raylib.h"
#include "raymath.h"
#include "components.h"
#include "mainSceneSystems.h"
#include <iostream>

namespace Scenes
{
    void respawnPlayer(TransformComponent &playerTransform)
    {
        // Implement respawn logic, e.g., set to a safe location
        playerTransform.position = Vector2{400, 300}; // Example respawn position
    }

    void splitOrRemoveAsteroid(entt::entity asteroid, entt::registry &registry)
    {
        // Implement logic to split asteroid into smaller pieces or remove
        // create a particle emitter with a timeout so it will disappear
        auto &asteroidTransform = registry.get<TransformComponent>(asteroid);

        auto emitterEntity = registry.create();
        auto &emitterComponent = registry.emplace<ParticleEmitterComponent>(emitterEntity);
        emitterComponent.position = Vector2{0, 0};
        emitterComponent.direction = Vector2{0, 0};
        emitterComponent.isActive = true;
        emitterComponent.randomness = 1.0F;
        emitterComponent.speed = 2.0F;
        emitterComponent.lifetimeEmittedParticles = .6F;
        emitterComponent.definition = ParticleDefinition {
            ParticleType::Basic,
            WHITE,
            ""
        };

        registry.emplace<TransformComponent>(emitterEntity, asteroidTransform.position, 0.0F);
        registry.emplace<TimeoutComponent>(emitterEntity, 0.3f);
        registry.destroy(asteroid); // Example removal
    }

    void updateScore()
    {
        // Implement score update logic
    }
    void collisionSystem(entt::registry &registry)
    {
        auto viewPlayers = registry.view<PlayerComponent, TransformComponent, ColliderComponent>();
        auto viewAsteroids = registry.view<AsteroidComponent, TransformComponent, ColliderComponent>();
        auto viewBullets = registry.view<BulletComponent, TransformComponent, ColliderComponent>();

        for (auto entity : viewPlayers)
        {
            auto &playerTransform = viewPlayers.get<TransformComponent>(entity);
            auto &playerCollider = viewPlayers.get<ColliderComponent>(entity);

            for (auto asteroid : viewAsteroids)
            {
                auto &asteroidTransform = viewAsteroids.get<TransformComponent>(asteroid);
                auto &asteroidCollider = viewAsteroids.get<ColliderComponent>(asteroid);

                float distance = Vector2Distance(playerTransform.position, asteroidTransform.position);
                if (distance < (playerCollider.radius + asteroidCollider.radius))
                {
                    // Resolve Player-Asteroid Collision
                    auto &player = viewPlayers.get<PlayerComponent>(entity);
                    player.lives--;
                    player.isAlive = false;
                    std::cout << "Player boom" << std::endl;
                    // Handle player respawn logic
                    respawnPlayer(playerTransform);
                    // Handle asteroid splitting or removal
                    splitOrRemoveAsteroid(asteroid, registry);
                }
            }
        }

        for (auto bullet : viewBullets)
        {
            auto &bulletTransform = viewBullets.get<TransformComponent>(bullet);
            auto &bulletCollider = viewBullets.get<ColliderComponent>(bullet);

            for (auto asteroid : viewAsteroids)
            {
                auto &asteroidTransform = viewAsteroids.get<TransformComponent>(asteroid);
                auto &asteroidCollider = viewAsteroids.get<ColliderComponent>(asteroid);

                float distance = Vector2Distance(bulletTransform.position, asteroidTransform.position);
                if (distance < (bulletCollider.radius + asteroidCollider.radius))
                {
                    // Resolve Bullet-Asteroid Collision
                    registry.destroy(bullet);
                    splitOrRemoveAsteroid(asteroid, registry);
                    // Update score or game metrics
                    updateScore();
                }
            }
        }
    }

}