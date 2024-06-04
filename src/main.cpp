#ifndef ASSETS_PATH
#define ASSETS_PATH
#endif

#include <iostream>
#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "Title");
    SetTargetFPS(60);

    Camera2D mainCamera;
    mainCamera.zoom = 1;
    mainCamera.offset = {(float)(GetScreenWidth() / 2), (float)(GetScreenHeight() / 2)};
    mainCamera.rotation = 0;
    mainCamera.target = {0, 0};

    Texture2D background = LoadTexture(ASSETS_PATH "Flat Night 4 BG.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawTexture(background, 0, 0, WHITE);
        BeginMode2D(mainCamera);
        DrawText("This is a new window", 0, 0, 10, WHITE);
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
}