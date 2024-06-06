#pragma once
#include "appConfig.h"
#include <memory>
#include "sceneManager.h"
#include "assetManager.h"
namespace Core
{

    class App
    {
    private:
        static App *s_instance;
        SceneManager *m_sceneManager; // only one pointer to it. does it make sense? I didn't do it with the config
        AssetManager *m_assetManager;

    public:
        static App &GetInstance();       // the app getter is static
        SceneManager &GetSceneManager(); // but the scene manager is part of the app
        
        AssetManager &GetAssetManager(); // asset manager

    private:
        // this member will always be valid until the app dies
        AppConfig m_config;

    public:
        App(AppConfig config);

        // so a pointer to this configuration shouldn't be a problem
        AppConfig &GetConfig() { return m_config; }

        void Run();
    };
}