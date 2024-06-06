#include "mainScene.h"
#include "mainScene/mainSceneSystems.h"
#include "raylib.h"
#include "raymath.h"
#include "components.h"
#include "entt/entt.hpp"
#include "app.h"

namespace Scenes
{
    entt::registry registry;
    MainScene::MainScene() {}
    void particleEmitSystem(entt::registry &registry)
    {
        auto view = registry.view<ParticleEmitterComponent, TransformComponent>();
        for (auto entity : view)
        {
            auto &emitter = view.get<ParticleEmitterComponent>(entity);
            auto &transform = view.get<TransformComponent>(entity);
            if (emitter.isActive)
            {
                // TODO: maybe I should use a different registry, only for the particles
                // spawn particle
                auto entity = registry.create();
                // spawn point
                Vector2 spawnPoint = Vector2Add(transform.position, emitter.position);

                Vector2 randomDirection = {
                    (emitter.direction.x + (GetRandomValue(-100, 100) / 100.0f) * emitter.randomness) * emitter.speed,
                    (emitter.direction.y + (GetRandomValue(-100, 100) / 100.0f) * emitter.randomness) * emitter.speed};
                // 1 second lifetime
                switch (emitter.definition.type)
                {
                case ParticleType::Basic:
                    registry.emplace<ParticleComponent>(entity, spawnPoint, Vector2Normalize(randomDirection), emitter.definition.color);
                case ParticleType::Sprite:
                    registry.emplace<ParticleSpriteComponent>(entity, spawnPoint,
                                                              Vector2Normalize(randomDirection), emitter.definition.spriteAlias);
                }
                registry.emplace<TimeoutComponent>(entity, emitter.lifetimeEmittedParticles); // use the timeout component to get rid of the particle!
            }
        }
    }

    void particleUpdateSystem(entt::registry &registry)
    {
        auto view = registry.view<ParticleComponent>();
        for (auto entity : view)
        {
            auto &particle = view.get<ParticleComponent>(entity);
            particle.position.x += particle.velocity.x * 50 * GetFrameTime();
            particle.position.y += particle.velocity.y * 50 * GetFrameTime();
        }
    }

    void renderParticleSystem(entt::registry &registry)
    {
        auto view = registry.view<ParticleComponent>();
        for (auto entity : view)
        {
            auto &particle = view.get<ParticleComponent>(entity);
            DrawCircleV(particle.position, 2, particle.color);
        }
    }

    void createPlayer(entt::registry &registry)
    {
        auto entity = registry.create();
        registry.emplace<TransformComponent>(entity, Vector2{400, 300}, -90.0f); // Starting position and rotation
        registry.emplace<VelocityComponent>(entity, Vector2{0, 0}, 0.0f);        // Initial velocity and rotation speed
        registry.emplace<ColliderComponent>(entity, 20.0f);                      // Collider radius
        registry.emplace<RenderComponent>(entity, BLACK, ShapeType::Square);     // Render color
        registry.emplace<ParticleEmitterComponent>(entity, Vector2{0, 0}, Vector2{0, 10}, false, 0.8F, 5.0F, .8F);
        registry.emplace<PlayerComponent>(entity, true, 3);                          // Player is alive with 3 lives
        registry.emplace<InputComponent>(entity, false, false, false, false, false); // Initial input state
    }
    void createCamera(entt::registry &registry)
    {
        auto config = Core::App::GetInstance().GetConfig();
        auto entity = registry.create();
        Camera2D camera;
        camera.zoom = 1;
        camera.offset = {config.Width / 2, config.Height / 2};
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
        particleEmitSystem(registry);
        particleUpdateSystem(registry);
    }

    void MainScene::Draw()
    {
        auto config = Core::App::GetInstance().GetConfig();
        BeginDrawing();
        ClearBackground({0xde, 0xe4, 0xe7, 0xff});
        // draw background without entities :)

        Texture2D bg = Core::App::GetInstance().GetAssetManager().getTexture("default_background");
        DrawTextureV(bg, {0, 0}, WHITE);
        beginCameraSystem(registry);
        renderSystem(registry);

        DrawRectangleLines(0, 0, config.Width, config.Height, BLACK);
        DrawRectangleLines(+5, +5, config.Width - 10, config.Height - 10, BLACK);
        renderParticleSystem(registry);
        renderDebugPlayer(registry);
        endCameraSystem(registry);
        renderHUD(registry);

        DrawRectangleLines(-10, -10, 10, 10, BLACK);

        DrawFPS(20, 100);
        EndDrawing();
    }
}