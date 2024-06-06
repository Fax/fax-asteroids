#include "entt/entt.hpp"
#include "raylib.h"
#include "components.h"
#include "mainSceneSystems.h"

namespace Scenes
{
    void inputSystem(entt::registry &registry)
    {
        auto view = registry.view<InputComponent>();

        for (auto entity : view)
        {
            auto &input = view.get<InputComponent>(entity);

            input.up = IsKeyDown(KEY_W);
            input.down = IsKeyDown(KEY_S);
            input.left = IsKeyDown(KEY_A);
            input.right = IsKeyDown(KEY_D);
            input.shoot = IsKeyPressed(KEY_SPACE);
            input.scrollUp = GetMouseWheelMove() > 0;
            input.scrollDown = GetMouseWheelMove() < 0;
        }
    }

}