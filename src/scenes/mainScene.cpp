#include "mainScene.h"
#include "mainScene/mainSceneSystems.h"
#include "raylib.h"
#include "raymath.h"
#include "components.h"
#include "entt/entt.hpp"
#include "app.h"
namespace Scenes
{
    void createPlayer(entt::registry &registry)
    {
        auto entity = registry.create();
        registry.emplace<TransformComponent>(entity, Vector2{400, 300}, -90.0f);     // Starting position and rotation
        registry.emplace<VelocityComponent>(entity, Vector2{0, 0}, 0.0f);            // Initial velocity and rotation speed
        registry.emplace<ColliderComponent>(entity, 20.0f);                          // Collider radius
        registry.emplace<RenderComponent>(entity, BLACK, ShapeType::Square);         // Render color
        registry.emplace<PlayerComponent>(entity, true, 3);                          // Player is alive with 3 lives
        registry.emplace<InputComponent>(entity, false, false, false, false, false); // Initial input state
    }
    void createCamera(entt::registry &registry)
    {
        auto config = Core::App::GetInstance().GetConfig();
        auto entity = registry.create();
        Camera2D camera;
        camera.zoom = 1;
        camera.offset = {config.Width/2, config.Height/2};
        camera.target = {400, 300};
        camera.rotation = 0;
        registry.emplace<CameraComponent>(entity, camera, true);
    }
    void createAsteroid(entt::registry &registry, Vector2 position, Vector2 velocity, float radius)
    {
        auto entity = registry.create();
        registry.emplace<TransformComponent>(entity, position, 0.0f);
        registry.emplace<VelocityComponent>(entity, velocity, 0.0f);
        registry.emplace<ColliderComponent>(entity, radius);
        registry.emplace<RenderComponent>(entity, BLUE, ShapeType::Circle);
        registry.emplace<AsteroidComponent>(entity, 3); // Example size
    }
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
            }
        }
    }
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
    void renderDebugPlayer(entt::registry &registry)
    {
        auto view = registry.view<PlayerComponent, TransformComponent, VelocityComponent>();
        for (auto entity : view)
        {
            auto &player = view.get<PlayerComponent>(entity);
            auto &transform = view.get<TransformComponent>(entity);
            auto &velocity = view.get<VelocityComponent>(entity);

            DrawLine(transform.position.x, transform.position.y, transform.position.x + velocity.velocity.x, transform.position.y + velocity.velocity.y, GREEN);
            DrawLine(transform.position.x, transform.position.y, transform.position.x + transform.getForward().x * 20, transform.position.y + transform.getForward().y * 20, RED);
        }
    }
    void cameraSystem(entt::registry &registry)
    {
        auto view = registry.view<CameraComponent>();
        auto playerView = registry.view<PlayerComponent, TransformComponent>();
        for (auto entity : view)
        {
            auto &camera = view.get<CameraComponent>(entity);
            if (camera.isActive)
            {
                const auto &entity = playerView.back();
                if (entity != entt::null)
                {
                    auto &transform = playerView.get<TransformComponent>(entity);
                    camera.camera.target = Vector2Lerp(camera.camera.target, transform.position, .1);
                }
            }
        }
    }
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
    entt::registry registry;
    MainScene::MainScene() {}
    void MainScene::Load()
    {

        createAsteroid(registry, Vector2{200, 200}, Vector2{50, 50}, 30.0f);
        createAsteroid(registry, Vector2{600, 400}, Vector2{-50, -30}, 20.0f);
        createAsteroid(registry, Vector2{140, 100}, Vector2{-10, 30}, 20.0f);
        createPlayer(registry);
        createCamera(registry);
    }
    void MainScene::Update(float dt)
    {
        inputSystem(registry);
        movementSystem(registry);
        playerSystem(registry);
        // asteroidSystem(registry);
        shootSystem(registry);
        timeoutSystem(registry);
        cameraSystem(registry);
        collisionSystem(registry);
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

    void MainScene::Draw()
    {
        auto config = Core::App::GetInstance().GetConfig();
        BeginDrawing();
        ClearBackground({0xde, 0xe4, 0xe7, 0xff});
        beginCameraSystem(registry);
        renderSystem(registry);
        
        DrawRectangleLines(0,0,config.Width,  config.Height, BLACK);
        DrawRectangleLines(+5,+5,config.Width-10,  config.Height-10, BLACK);

        renderDebugPlayer(registry);
        endCameraSystem(registry);
        renderHUD(registry);

        DrawRectangleLines(-10, -10, 10, 10, BLACK);

        DrawFPS(20, 100);
        EndDrawing();
    }
}