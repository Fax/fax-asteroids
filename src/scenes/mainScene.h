#pragma once
#include "scene.h"
namespace Scenes
{
    class MainScene : public Core::BScene
    {
    public:
        MainScene();
        void Draw() ;
        void Load() ;
        void Update(float dt) ;
    };
}