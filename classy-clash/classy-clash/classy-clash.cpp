// classy-clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"

constexpr int screen_width{384};
constexpr int screen_height{384};

int main()
{
    InitWindow(screen_width, screen_height, "Classy Clash");
    SetTargetFPS(60);


#pragma region Texture Loading
    const Texture2D t_game_map = LoadTexture("nature_tileset/game-map_v2.png");
#pragma endregion


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(t_game_map, {0, 0}, 0, 4, WHITE);
        EndDrawing();
    }

    CloseWindow();
}
