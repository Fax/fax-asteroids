#ifndef ASSETS_PATH
#define ASSETS_PATH
#endif

#include <iostream>
#include "raylib.h"
#include "app.h"
#include "appConfig.h"
#include "entt/entt.hpp"

int main(void)
{
    std::cout << "init" << std::endl;
    AppConfig cfg;
    Core::App app(cfg);
    app.Run();

    return 0;
}

// int main(void)
// {
//     const int screenWidth = 800;
//     const int screenHeight = 450;
//     InitWindow(screenWidth, screenHeight, "Title");
//     SetTargetFPS(60);

//     Camera c3;
//     c3.position = {10, 20, 20};
//     c3.target = {0, 0, 0};
//     c3.up = (Vector3){0.0f, 1.0f, 0.0f};
//     c3.fovy = 45.0f;
//     c3.projection = CAMERA_PERSPECTIVE;
//     Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
//     Vector3 cubeSize = {2.0f, 2.0f, 2.0f};

//     Ray ray;                      // Picking line ray
//     RayCollision collision = {0}; // Ray collision hit info
//     while (!WindowShouldClose())
//     {
//         if (IsCursorHidden())
//             UpdateCamera(&c3, CAMERA_FIRST_PERSON);
//         if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
//         {
//             if (IsCursorHidden())
//                 EnableCursor();
//             else
//                 DisableCursor();
//         }
//         if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
//         {
//             if (!collision.hit)
//             {
//                 ray = GetMouseRay(GetMousePosition(), c3);

//                 // Check collision between ray and box
//                 collision = GetRayCollisionBox(ray,
//                                                (BoundingBox){(Vector3){cubePosition.x - cubeSize.x / 2, cubePosition.y - cubeSize.y / 2, cubePosition.z - cubeSize.z / 2},
//                                                              (Vector3){cubePosition.x + cubeSize.x / 2, cubePosition.y + cubeSize.y / 2, cubePosition.z + cubeSize.z / 2}});
//                 std::cout << "collision checked" << std::endl;
//             }
//             else
//                 collision.hit = false;
//         }
//         BeginDrawing();
//         ClearBackground(LIGHTGRAY);
//         BeginMode3D(c3);
//         if (collision.hit)
//         {
//             DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RED);
//             DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, MAROON);

//             DrawCubeWires(cubePosition, cubeSize.x + 0.2f, cubeSize.y + 0.2f, cubeSize.z + 0.2f, GREEN);
//         }
//         else
//         {
//             DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, GRAY);
//             DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, DARKGRAY);
//         }
//         DrawCubeV(cubePosition, cubeSize, RED);
//         DrawCubeWiresV(cubePosition, cubeSize, MAROON);
//         DrawRay(ray, GREEN);
//         DrawGrid(10, 1.0f);
//         EndMode3D();
//         DrawText("Try clicking on the box with your mouse!", 240, 10, 20, DARKGRAY);

//         if (collision.hit)
//             DrawText("BOX SELECTED", (screenWidth - MeasureText("BOX SELECTED", 30)) / 2, (int)(screenHeight * 0.1f), 30, GREEN);

//         DrawText("Right click mouse to toggle camera controls", 10, 430, 10, GRAY);
//         DrawFPS(10, 10);
//         EndDrawing();
//     }
//     CloseWindow();
// }