// classy-clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"
#include "raymath.h"

constexpr int screen_width{384};
constexpr int screen_height{384};
constexpr int map_scale{4};

int main()
{
    InitWindow(screen_width, screen_height, "Classy Clash");
    SetTargetFPS(60);


#pragma region Texture Loading
    const Texture2D t_game_map = LoadTexture("nature_tileset/game-map_v2.png");
#pragma endregion

    const Vector2 min_map_pos{
        -static_cast<float>(t_game_map.width * map_scale - screen_width),
        -static_cast<float>(t_game_map.height * map_scale - screen_height)
    };
    constexpr Vector2 max_map_pos{0, 0};
    constexpr float speed{4.0f};
    Vector2 map_pos{0, 0};

    while (!WindowShouldClose())
    {
        Vector2 direction{0.0f, 0.0f};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
        if (IsKeyDown(KEY_D)) direction.x += 1.0f;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
        if (IsKeyDown(KEY_S)) direction.y += 1.0f;

        if (Vector2Length(direction) > 0.0f)
        {
            map_pos = Vector2Subtract(map_pos, Vector2Scale(Vector2Normalize(direction), speed));
            map_pos = Vector2Clamp(map_pos, min_map_pos, max_map_pos);
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(t_game_map, map_pos, 0, map_scale, WHITE);
        EndDrawing();
    }

    CloseWindow();
}
