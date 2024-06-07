#include "entt/entt.hpp"
#include "app.h"
#include "raylib.h"
#include "raymath.h"
#include "components.h"
#include "mainSceneSystems.h"

namespace Scenes
{
    void createBullet(entt::registry &registry, Vector2 position, Vector2 velocity, BulletType type)
    {
        auto entity = registry.create();
        registry.emplace<TransformComponent>(entity, position, 0.0f);
        registry.emplace<VelocityComponent>(entity, velocity, 0.0f); // the velocity vector is defined by the forward of the shooter
        registry.emplace<ColliderComponent>(entity, 5.0f);
        registry.emplace<TimeoutComponent>(entity, 5.0f, 0.0f);
        switch (type)
        {
        case BulletType::Square:
            /* code */
            registry.emplace<RenderComponent>(entity, RED, ShapeType::Square, 2.0f);
            break;
        case BulletType::Circle:
            /* code */
            registry.emplace<RenderComponent>(entity, WHITE, ShapeType::Circle, 2.0f);
            break;
        default:
            registry.emplace<RenderComponent>(entity, BLUE, ShapeType::Circle, 2.0f);
            break;
        }
        registry.emplace<BulletComponent>(entity, type); // Example size
    }

    void shootSystem(entt::registry &registry)
    {
        auto view = registry.view<InputComponent, TransformComponent, VelocityComponent>();
        for (auto entity : view)
        {
            auto &transform = view.get<TransformComponent>(entity);
            auto &input = view.get<InputComponent>(entity);
            auto &velocity = view.get<VelocityComponent>(entity);
            if (input.shoot)
            {

                Vector2 fw = transform.getForward();
                float bulletSpeed = 200;
                createBullet(registry, Vector2Add(transform.position, fw), Vector2Add(velocity.velocity, Vector2Multiply({bulletSpeed, bulletSpeed}, Vector2Normalize(fw))), BulletType::Circle);
                Core::App::GetInstance().GetAssetManager().playSound("shoot",1);
            }
        }
    }

}