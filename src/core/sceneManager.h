#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "scene.h"
namespace Core
{

     class SceneManager
    {
    private:
        std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
        Scene *currentScene;

    public:
        SceneManager() : currentScene(nullptr) {}
        ~SceneManager();
        // Add a scene to the manager
        void AddScene(const std::string &name, Scene *scene);

        // Remove a scene from the manager
        void RemoveScene(const std::string &name);

        // Change the current scene
        void ChangeScene(const std::string &name);

        // Update the current scene
        void UpdateCurrentScene(float dt);
        void OncePerSecond();
        // Draw the current scene
        void DrawCurrentScene();
    };
}