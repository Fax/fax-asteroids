#pragma once
#include <string>

namespace Core
{

    class Scene
    {
    public:
        virtual ~Scene() = default;
        virtual void Load() = 0;
        virtual void Unload() = 0;
        virtual void Update(float dt) = 0;
        virtual void OncePerSecond() = 0;
        virtual void Draw() = 0;
    };

    class BScene : public Scene
    {
    public:
        void Update(float dt) override {}
        void OncePerSecond() override {}
        void Draw() override {}
        void Load() override {}
        void Unload() override {}
    };
}