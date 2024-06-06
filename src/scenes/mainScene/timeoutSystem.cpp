#include "entt/entt.hpp"
#include "raylib.h"
#include "components.h"
#include "mainSceneSystems.h"

namespace Scenes
{
    void timeoutSystem(entt::registry &registry)
    {
        auto view = registry.view<TimeoutComponent>();
        for (auto entity : view)
        {
            auto &timeout = view.get<TimeoutComponent>(entity);
            timeout.current += GetFrameTime();
            if (timeout.current > timeout.timeout)
            {
                registry.destroy(entity);
            }
        }
    }

}