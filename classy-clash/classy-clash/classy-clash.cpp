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
    const Texture2D t_knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
#pragma endregion

#pragma region Map Variables
    const Vector2 min_map_pos{
        -static_cast<float>(t_game_map.width * map_scale - screen_width),
        -static_cast<float>(t_game_map.height * map_scale - screen_height)
    };
    constexpr Vector2 max_map_pos{0, 0};
    Vector2 map_pos{0, 0};
#pragma endregion

    Vector2 knight_pos{
        (screen_width / 2.0f - 4.0f * 0.5f * static_cast<float>(t_knight_idle.width) / 6.0f),
        static_cast<float>(screen_height) / 2.0f - 4.0f * 0.5f * static_cast<float>(t_knight_idle.height)
    };

    constexpr float speed{4.0f};
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

        Rectangle knight_source_rect{
            0,
            0,
            static_cast<float>(t_knight_idle.width) / 6.0f,
            static_cast<float>(t_knight_idle.height)
        };

        Rectangle knight_dest_rect{
            knight_pos.x,
            knight_pos.y,
            map_scale * static_cast<float>(t_knight_idle.width) / 6.0f,
            map_scale * static_cast<float>(t_knight_idle.height)
        };

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(t_game_map, map_pos, 0, map_scale, WHITE);
        DrawTexturePro(t_knight_idle, knight_source_rect, knight_dest_rect, Vector2Zero(), 0,WHITE);
        EndDrawing();
    }
    UnloadTexture(t_game_map);
    UnloadTexture(t_knight_idle);
    CloseWindow();
}
