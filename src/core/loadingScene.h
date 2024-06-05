#pragma once
#include "scene.h"
namespace Core
{

    class LoadingScene : public BScene
    {
    public:
        LoadingScene();
        void Update(float dt);
        void Draw();
    };
}