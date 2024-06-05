#include "entt/entt.hpp"
#include "raylib.h"
#include "mainSceneSystems.h"
#include "components.h"
#include "raymath.h"

namespace Scenes
{

    void asteroidSystem(entt::registry &registry)
    {
        auto view = registry.view<AsteroidComponent, TransformComponent, VelocityComponent>();

        for (auto entity : view)
        {
            auto &transform = view.get<TransformComponent>(entity);
            auto &velocity = view.get<VelocityComponent>(entity);

            // Update asteroid position
            transform.position.x += velocity.velocity.x * GetFrameTime();
            transform.position.y += velocity.velocity.y * GetFrameTime();

            // Implement asteroid wrapping around screen edges
            if (transform.position.x > 800)
                transform.position.x = 0;
            if (transform.position.x < 0)
                transform.position.x = 800;
            if (transform.position.y > 600)
                transform.position.y = 0;
            if (transform.position.y < 0)
                transform.position.y = 600;
        }
    }
}