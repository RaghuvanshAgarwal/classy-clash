#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "character.h"

constexpr int screen_width{384};
constexpr int screen_height{384};
constexpr float map_scale{4.0f};

int main()
{
    InitWindow(screen_width, screen_height, "Classy Clash");
    SetTargetFPS(60);


#pragma region Texture Loading
    const Texture2D t_game_map = LoadTexture("nature_tileset/game-map_v2.png");
    const Texture2D t_knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    const Texture2D t_knight_run = LoadTexture("characters/knight_run_spritesheet.png");
#pragma endregion

#pragma region Map Variables
    const Vector2 max_map_pos{
        static_cast<float>(t_game_map.width * map_scale - screen_width),
        static_cast<float>(t_game_map.height * map_scale - screen_height)
    };
    constexpr Vector2 min_map_pos{0, 0};
#pragma endregion


    character knight(t_knight_idle, t_knight_run, map_scale);
    knight.set_screen_pos(screen_width, screen_height);
    knight.set_map_pos(min_map_pos, Vector2Scale(max_map_pos, 1));

    
    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();
        knight.tick(dt);
        Vector2 map_pos = Vector2Scale(knight.get_world_pos(), -1.0f);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(t_game_map, map_pos, 0, map_scale, WHITE); // Draw the map
        knight.draw();
        EndDrawing();
    }
#pragma region Texture Unloading
    UnloadTexture(t_game_map);
    UnloadTexture(t_knight_idle);
    UnloadTexture(t_knight_run);
#pragma endregion
    CloseWindow();
}
