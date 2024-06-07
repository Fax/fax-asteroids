#pragma once
#include <string>
#include "raylib.h"

struct ParticleComponent {
    Vector2 position;
    Vector2 velocity;
    Color color = RED;
};
struct ParticleSpriteComponent {
    Vector2 position;
    Vector2 velocity;
    std::string spriteAlias;
};
enum class ParticleType{
    Basic,
    Sprite
};
struct ParticleDefinition{
    ParticleType type = ParticleType::Basic;
    Color color = RED;
    std::string spriteAlias;
};
struct ParticleEmitterComponent{
    Vector2 position;
    Vector2 direction;
    bool isActive = false;
    float randomness = 0.0F;
    float speed = 5.0F;
    float lifetimeEmittedParticles = 1.0F;
    ParticleDefinition definition;
};

enum class BulletType {
    Circle,
    Square,
    // Add more shapes as needed
};

struct BulletComponent {
    BulletType type;
};
struct TimeoutComponent{
    float timeout;
    float current;
};

enum class ShapeType {
    Triangle,
    Circle,
    Square,
    Sprite,
    // Add more shapes as needed
};

struct TransformComponent {
    Vector2 position;
    float rotation;
    Vector2 getForward()const {
        float rad = DEG2RAD * rotation;
        return {
            cos(rad),
            sin(rad)
        };
    }
};

struct VelocityComponent {
    Vector2 velocity;
    float rotationSpeed;
};

struct ColliderComponent {
    float radius;
};
struct CameraComponent {
    Camera2D camera;
    bool isActive = false;
};

struct RenderComponent {
    Color color;
    ShapeType shape;
    float size = 10;
    std::string spriteAlias;
    float spriteRotation = 0;
};

struct PlayerComponent {
    bool isAlive;
    int lives;
};

struct InputComponent {
    bool up;
    bool down;
    bool left;
    bool right;
    bool shoot;
    bool scrollUp;
    bool scrollDown;
};

struct AsteroidComponent {
    int size;
};



struct SpriteComponent {
    Texture2D texture; // should I store the pointer only?
    Rectangle sourceRect; // Source rectangle for sprite sheet
    Color color;
    int frameIndex; // Current frame index for animations
    int frameCount; // Total number of frames
};
