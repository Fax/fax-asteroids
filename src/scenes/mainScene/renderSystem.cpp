#include "entt/entt.hpp"
#include "raylib.h"
#include "raymath.h"
#include "components.h"
#include "mainSceneSystems.h"

namespace Scenes
{
    void renderSystem(entt::registry &registry)
    {
        auto view = registry.view<TransformComponent, RenderComponent>();

        for (auto entity : view)
        {
            auto &transform = view.get<TransformComponent>(entity);
            auto &render = view.get<RenderComponent>(entity);

            switch (render.shape)
            {
            case ShapeType::Triangle:
            {
                break;
            }
            case ShapeType::Square:
            {
                // DrawRectangleV(transform.position, {20, 20}, render.color);
                DrawRectanglePro({transform.position.x, transform.position.y, render.size, render.size}, {render.size / 2, render.size / 2}, transform.rotation, render.color);
                break;
            }
            case ShapeType::Circle:
            {
                DrawCircle(transform.position.x, transform.position.y, render.size, render.color);
                break;
            }
                // Add more shape cases as needed
            }
        }
    }

}