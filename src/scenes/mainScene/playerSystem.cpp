#include "entt/entt.hpp"
#include "raylib.h"
#include "raymath.h"
#include "mainSceneSystems.h"
#include "components.h"

namespace Scenes
{

    void playerSystem(entt::registry &registry)
    {
        auto view = registry.view<PlayerComponent, TransformComponent, VelocityComponent, InputComponent>();
        float dt = GetFrameTime();
        for (auto entity : view)
        {
            auto &player = view.get<PlayerComponent>(entity);
            auto &transform = view.get<TransformComponent>(entity);
            auto &velocity = view.get<VelocityComponent>(entity);
            auto &input = view.get<InputComponent>(entity);

            if (!player.isAlive)
            {
                // Handle respawn logic
                player.isAlive = true;
                transform.position = Vector2{400, 300}; // Example respawn position
                velocity.velocity = Vector2{0, 0};
            }

            // Apply input to player movement and rotation
            if (input.up)
            {
                velocity.velocity.x += transform.getForward().x * dt * 50;
                velocity.velocity.y += transform.getForward().y * dt * 50;
            }
            if (input.down) // it decelerates the CURRENT velocity vector, not facing direction
            {
                Vector2 bw = {velocity.velocity.x * -1, velocity.velocity.y * -1};
                velocity.velocity.x += bw.x * dt *2;
                velocity.velocity.y += bw.y * dt *2;
            }
            if (input.left)
            {
                transform.rotation -= 90 * dt;
            }
            if (input.right)
            {
                transform.rotation += 90 * dt;
            }
            if (input.shoot)
            {
                velocity.velocity = {0, 0};
            }
            if (!input.up && !input.down)
            {
                // friction

                velocity.velocity.x = Lerp(velocity.velocity.x, 0, .01);
                velocity.velocity.y = Lerp(velocity.velocity.y, 0, .01);
            }
        }
    }

}