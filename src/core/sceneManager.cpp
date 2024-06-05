#include "sceneManager.h"
namespace Core
{

    void SceneManager::AddScene(const std::string &name, Scene *scene)
    {
        scenes[name].reset(scene);
    }

    // Remove a scene from the manager
    void SceneManager::RemoveScene(const std::string &name)
    {
        scenes.erase(name);
    }

    // Change the current scene
    void SceneManager::ChangeScene(const std::string &name)
    {
        if (scenes.find(name) != scenes.end())
        {
            if (currentScene)
            {
                currentScene->Unload();
            }
            currentScene = scenes[name].get();
            currentScene->Load();
        }
    }

    SceneManager::~SceneManager()
    {
        if (currentScene)
        {
            currentScene->Unload();
        }
        // delete currentScene;
    }

    // Update the current scene
    void SceneManager::UpdateCurrentScene(float dt)
    {
        if (currentScene)
        {
            currentScene->Update(dt);
        }
    }
    void SceneManager::OncePerSecond()
    {
        if (currentScene)
        {
            currentScene->OncePerSecond();
        }
    }

    // Draw the current scene
    void SceneManager::DrawCurrentScene()
    {
        if (currentScene)
        {
            currentScene->Draw();
        }
    }
}