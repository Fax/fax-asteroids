#include "entt/entt.hpp"
namespace Scenes
{

        void inputSystem(entt::registry &registry);
        void playerSystem(entt::registry &registry);
        void movementSystem(entt::registry &registry);
        void asteroidSystem(entt::registry &registry);
        void renderSystem(entt::registry &registry);
        void renderHUD(entt::registry &registry);
        void shootSystem(entt::registry &registry);
        void timeoutSystem(entt::registry &registry);
        void renderSystem(entt::registry &registry);
        void collisionSystem(entt::registry &registry);



        void cameraSystem(entt::registry &registry);
        void beginCameraSystem(entt::registry &registry);
        void endCameraSystem(entt::registry &registry);
}