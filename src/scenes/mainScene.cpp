#include "mainScene.h"
#include "mainScene/mainSceneSystems.h"
#include "raylib.h"
#include "raymath.h"
#include "components.h"
#include "entt/entt.hpp"

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
    void createAsteroid(entt::registry &registry, Vector2 position, Vector2 velocity, float radius)
    {
        auto entity = registry.create();
        registry.emplace<TransformComponent>(entity, position, 0.0f);
        registry.emplace<VelocityComponent>(entity, velocity, 0.0f);
        registry.emplace<ColliderComponent>(entity, radius);
        registry.emplace<RenderComponent>(entity, BLUE, ShapeType::Circle);
        registry.emplace<AsteroidComponent>(entity, 3); // Example size
    }
     
   
    void renderDebugPlayer(entt::registry &registry)
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
            DrawText(TextFormat("Dt: %0.2f", GetFrameTime()), 20, 50, 10, BLACK);
            DrawLine(transform.position.x, transform.position.y, transform.position.x + velocity.velocity.x, transform.position.y + velocity.velocity.y, GREEN);
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
                DrawRectanglePro({transform.position.x, transform.position.y, 20, 20}, {10, 10}, transform.rotation, render.color);
                break;
            }
            case ShapeType::Circle:
            {
                DrawCircle(transform.position.x, transform.position.y, 20, render.color);
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
    }
    void MainScene::Update(float dt)
    {
        inputSystem(registry);
        movementSystem(registry);
        playerSystem(registry);
        asteroidSystem(registry);
    }
    void MainScene::Draw()
    {
        BeginDrawing();
        ClearBackground(PURPLE);
        renderSystem(registry);
        renderDebugPlayer(registry);
        DrawFPS(100,100);
        EndDrawing();
    }
}