#include "raylib.h"
#include "loadingScene.h"
#include "app.h"
#include "mainScene.h"
namespace Core
{

    LoadingScene::LoadingScene() {}

    void LoadingScene::Draw()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Loading...", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    float delta = 0.0f;
    void LoadingScene::Update(float dt)
    {
        delta += dt;
        if (IsKeyPressed(KEY_ENTER) || delta > 1)
        {
            // Assume that you have another scene to transition to, e.g., "MainScene"
            App::GetInstance().GetSceneManager().AddScene("MainScene", new Scenes::MainScene());
            App::GetInstance().GetSceneManager().ChangeScene("MainScene");
        }
    }

}