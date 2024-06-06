#include "entt/entt.hpp"
#include "raylib.h"
#include "raymath.h"
#include "components.h"
#include "mainSceneSystems.h"

namespace Scenes
{
    void cameraSystem(entt::registry &registry)
    {
        auto view = registry.view<CameraComponent>();
        auto playerView = registry.view<PlayerComponent, TransformComponent,InputComponent>();
        for (auto entity : view)
        {
            auto &camera = view.get<CameraComponent>(entity);
            if (camera.isActive)
            {
                const auto &entity = playerView.back();
                if (entity != entt::null)
                {
                    auto &transform = playerView.get<TransformComponent>(entity);
                    auto &input = playerView.get<InputComponent>(entity);
                    camera.camera.target = Vector2Lerp(camera.camera.target, transform.position, .1);
                    if(input.scrollDown){
                        camera.camera.zoom -= .1;
                    }else if(input.scrollUp){
                        camera.camera.zoom += .1;
                    }
                }
            }
        }
    }
    void beginCameraSystem(entt::registry &registry)
    {
        auto view = registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto &camera = view.get<CameraComponent>(entity);
            if (camera.isActive)
                BeginMode2D(camera.camera);
        }
    }

    // only to close the camera IF a camera is actually on the scene
    void endCameraSystem(entt::registry &registry)
    {
        auto view = registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto &camera = view.get<CameraComponent>(entity);
            if (camera.isActive)
                EndMode2D();
        }
    }

}