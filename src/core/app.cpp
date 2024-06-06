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
        m_assetManager = new AssetManager();
        

        m_sceneManager = new SceneManager();
        m_sceneManager->AddScene("LoadingScene", new LoadingScene());
    }
    void App::Run()
    {
        // we create the window here.
        InitWindow(m_config.Width, m_config.Height, m_config.Title.c_str());
        m_assetManager->load("default_background", std::string(ASSETS_PATH) + "Flat Night 4 BG.png");
        // NOW load the scene. This will essentially run the Load method
        // if the scene needs to load assets, let it do it
        m_sceneManager->ChangeScene("LoadingScene");
        // We can't load anything if the window is not initalized!
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
    AssetManager &App::GetAssetManager()
    {
        return *m_assetManager;
    }
    SceneManager &App::GetSceneManager()
    {
        return *m_sceneManager;
    }
}