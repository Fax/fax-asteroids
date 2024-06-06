#include "entt/entt.hpp"
#include "raylib.h"
#include "components.h"
#include "mainSceneSystems.h"

namespace Scenes
{
    void renderHUD(entt::registry &registry)
    {
        auto view = registry.view<PlayerComponent, TransformComponent, VelocityComponent>();
        for (auto entity : view)
        {
            auto &player = view.get<PlayerComponent>(entity);
            auto &transform = view.get<TransformComponent>(entity);
            auto &velocity = view.get<VelocityComponent>(entity);
            DrawText(TextFormat("Angle: %0.2f", transform.rotation), 20, 20, 10, BLACK);
            DrawText(TextFormat("Position: x:%0.2f y:%0.2f", transform.position.x, transform.position.y), 20, 30, 10, BLACK);
            DrawText(TextFormat("Speed: x:%0.2f y:%0.2f", velocity.velocity.x, velocity.velocity.y), 20, 40, 10, BLACK);
            DrawText(TextFormat("Lives: %i", player.lives), 20, 50, 10, BLACK);
            DrawText(TextFormat("Dt: %0.2f", GetFrameTime()), 20, 60, 10, BLACK);
        }
    }

}