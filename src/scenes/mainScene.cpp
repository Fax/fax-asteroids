#include "mainScene.h"
#include "mainScene/mainSceneSystems.h"
#include "raylib.h"
#include "raymath.h"
#include "coremath.h"
#include "components.h"
#include "assetManager.h"
#include "entt/entt.hpp"
#include "app.h"

namespace Scenes
{
    entt::registry registry;
    MainScene::MainScene()
    {
    }

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
                // the spawn point doesn't take in account the rotation of the transform
                spawnPoint = RotateAroundPoint(spawnPoint, transform.position, transform.rotation + 90);

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
        auto view2 = registry.view<ParticleSpriteComponent>();

        for (auto entity : view)
        {
            auto &particle = view.get<ParticleComponent>(entity);
            particle.position.x += particle.velocity.x * 50 * GetFrameTime();
            particle.position.y += particle.velocity.y * 50 * GetFrameTime();
        }
        for (auto entity : view2)
        {
            auto &particle = view2.get<ParticleSpriteComponent>(entity);
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

        auto viewSpriteParticles = registry.view<ParticleSpriteComponent>();
        for (auto entity : viewSpriteParticles)
        {
            auto &particle = viewSpriteParticles.get<ParticleSpriteComponent>(entity);

            Texture2D particleTexture = Core::App::GetInstance().GetAssetManager().getTexture(particle.spriteAlias);
            Vector2 origin = {5.0f, 5.0f};
            DrawTexturePro(particleTexture, {0, 0, (float)particleTexture.width, (float)particleTexture.height}, {particle.position.x, particle.position.y, 10, 10}, origin, 0, WHITE);
        }
    }

    void createPlayer(entt::registry &registry)
    {
        auto entity = registry.create();
        registry.emplace<TransformComponent>(entity, Vector2{400, 300}, -90.0f);                              // Starting position and rotation
        registry.emplace<VelocityComponent>(entity, Vector2{0, 0}, 0.0f);                                     // Initial velocity and rotation speed
        registry.emplace<ColliderComponent>(entity, 20.0f);                                                   // Collider radius
        registry.emplace<RenderComponent>(entity, WHITE, ShapeType::Sprite, 50.0F, "sprite_mainship", 90.0f); // Render color
        auto &emitter = registry.emplace<ParticleEmitterComponent>(entity,
                                                                   Vector2{0, 10},
                                                                   Vector2{0, 10},
                                                                   false,
                                                                   0.8F,
                                                                   5.0F,
                                                                   .8F);
        emitter.definition.spriteAlias = "particle_dust";
        emitter.definition.type = ParticleType::Sprite;
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
            // auto &player = view.get<PlayerComponent>(entity);
            auto &transform = view.get<TransformComponent>(entity);
            auto &velocity = view.get<VelocityComponent>(entity);

            DrawLine(transform.position.x, transform.position.y, transform.position.x + velocity.velocity.x, transform.position.y + velocity.velocity.y, GREEN);
            DrawLine(transform.position.x, transform.position.y, transform.position.x + transform.getForward().x * 20, transform.position.y + transform.getForward().y * 20, RED);
        }
    }

    void MainScene::Load()
    {

        // load the textures

        auto &am = Core::App::GetInstance().GetAssetManager();
        am.load("sprite_mainship", std::string(ASSETS_PATH) + "sprites/Main Ship - Base - Full health.png");
        am.load("particle_dust", std::string(ASSETS_PATH) + "particles/dust_inverse.png");
        am.loadSound("shoot", std::string(ASSETS_PATH) + "audio/shoot.wav");
        am.loadSound("explosion", std::string(ASSETS_PATH) + "audio/explosion.wav");
        am.loadSound("engine", std::string(ASSETS_PATH) + "audio/swoosh.wav");
        am.loadSound("impact", std::string(ASSETS_PATH) + "audio/impact.wav");

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
        // this is a problem! I can't render particles AND the other things
        // and then expect all of them to be in the correct order!
        renderParticleSystem(registry);
        renderSystem(registry);

        DrawRectangleLines(0, 0, config.Width, config.Height, BLACK);
        DrawRectangleLines(+5, +5, config.Width - 10, config.Height - 10, BLACK);
        renderDebugPlayer(registry);
        endCameraSystem(registry);
        renderHUD(registry);

        DrawRectangleLines(-10, -10, 10, 10, BLACK);

        DrawFPS(20, 100);
        EndDrawing();
    }
}