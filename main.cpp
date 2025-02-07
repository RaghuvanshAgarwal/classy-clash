#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "config.h"

int main()
{
    InitWindow(config::screen_width, config::screen_height, "Classy Clash");
    SetTargetFPS(60);

#pragma region Texture Loading
    const Texture2D t_game_map = LoadTexture("nature_tileset/game-map_v2.png");
    const Texture2D t_knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    const Texture2D t_knight_run = LoadTexture("characters/knight_run_spritesheet.png");
#pragma endregion

    character knight(t_knight_idle, t_knight_run);
    
    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();
        knight.tick(dt);

#pragma region Map Boundary Check
        Vector2 current_world_pos = knight.get_world_pos();
        if(current_world_pos.x < 0 ||
        current_world_pos.y < 0 ||
        current_world_pos.x > t_game_map.width * config::map_scale - config::screen_width ||
        current_world_pos.y > t_game_map.height * config::map_scale - config::screen_height)
        {
            knight.undo_movement();
        }

#pragma endregion


        Vector2 map_pos = Vector2Scale(knight.get_world_pos(), -1.0f);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(t_game_map, map_pos, 0, config::map_scale, WHITE); // Draw the map
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
