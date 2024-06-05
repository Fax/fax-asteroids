#pragma once
#include <raylib.h>

enum class ShapeType {
    Triangle,
    Circle,
    Square,
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

struct RenderComponent {
    Color color;
    ShapeType shape;
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
};

struct AsteroidComponent {
    int size;
};

struct BulletComponent {
    float lifespan;
};

struct SpriteComponent {
    Texture2D texture; // should I store the pointer only?
    Rectangle sourceRect; // Source rectangle for sprite sheet
    Color color;
    int frameIndex; // Current frame index for animations
    int frameCount; // Total number of frames
};
