#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "config.h"
#include "enemy.h"

int main()
{
    InitWindow(config::screen_width, config::screen_height, "Classy Clash");
    SetTargetFPS(60);

#pragma region Texture Loading
    const Texture2D t_game_map = LoadTexture("nature_tileset/game-map_v2.png");
    const Texture2D t_knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    const Texture2D t_knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    const Texture2D t_rock = LoadTexture("nature_tileset/rock.png");
    const Texture2D t_log = LoadTexture("nature_tileset/log.png");
    const Texture2D t_goblin_idle = LoadTexture("characters/goblin_idle_spritesheet.png");
    const Texture2D t_goblin_run = LoadTexture("characters/goblin_run_spritesheet.png");
#pragma endregion

    character knight(t_knight_idle, t_knight_run);
    prop props[2] = {
        prop(Vector2{400.0f, 600.0f}, t_rock),
        prop(Vector2{600.0f, 400.0f}, t_log)};

    enemy goblin(t_goblin_idle, t_goblin_run, Vector2{400.0f, 400.0f});

    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();
        knight.tick(dt);

#pragma region Map Boundary Check
        Vector2 current_world_pos = knight.get_world_pos();
        if (current_world_pos.x < 0 ||
            current_world_pos.y < 0 ||
            current_world_pos.x > t_game_map.width * config::map_scale - config::screen_width ||
            current_world_pos.y > t_game_map.height * config::map_scale - config::screen_height)
        {
            knight.undo_movement();
        }
#pragma endregion

        const Vector2 map_pos = Vector2Scale(knight.get_world_pos(), -1.0f);
        for (prop &p : props)
        {
            if (CheckCollisionRecs(knight.get_collision_rect(), p.get_collision_rect(map_pos)))
            {
                knight.undo_movement();
            }
        }

        goblin.tick(dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(t_game_map, map_pos, 0, config::map_scale, WHITE); // Draw the map
        for (const prop &p : props)
        {
            p.draw(map_pos);
        }
        goblin.draw();
        knight.draw();
        EndDrawing();
    }
#pragma region Texture Unloading
    UnloadTexture(t_game_map);
    UnloadTexture(t_knight_idle);
    UnloadTexture(t_knight_run);
    UnloadTexture(t_rock);
    UnloadTexture(t_log);
    UnloadTexture(t_goblin_idle);
    UnloadTexture(t_goblin_run);
#pragma endregion
    CloseWindow();
}
