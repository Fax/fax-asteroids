#include "app.h"
#include "loadingScene.h"
#include "raylib.h"
#include <memory>

namespace Core
{
    App *App::s_instance = nullptr; // set it to null to start, so we know
    App::App(AppConfig config) : m_config(config)
    {
        s_instance = this;
        m_sceneManager = new SceneManager();
        m_sceneManager->AddScene("LoadingScene", new LoadingScene());
        m_sceneManager->ChangeScene("LoadingScene");
    }
    void App::Run()
    {
        // we create the window here.
        InitWindow(m_config.Width, m_config.Height, m_config.Title.c_str());
        // now we start the loading process
        SetTargetFPS(60);
        // load the loading scene, let the loading scene load all the other scenes
        while (!WindowShouldClose())
        {
            m_sceneManager->UpdateCurrentScene(GetFrameTime());
            m_sceneManager->DrawCurrentScene();
        }
        CloseWindow();
    }

    App &App::GetInstance()
    {
        return *s_instance;
    }

    SceneManager &App::GetSceneManager()
    {
        return *m_sceneManager;
    }
}