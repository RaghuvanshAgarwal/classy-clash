#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Config.h"
#include "Enemy.h"

int main()
{
    InitWindow(Config::kScreenWidth, Config::kScreenHeight, "Classy Clash");
    SetTargetFPS(60);

#pragma region Texture Loading
    const Texture2D tGameMap = LoadTexture("nature_tileset/game-map_v2.png");
    const Texture2D tKnightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    const Texture2D tKnightRun = LoadTexture("characters/knight_run_spritesheet.png");
    const Texture2D tRock = LoadTexture("nature_tileset/rock.png");
    const Texture2D tLog = LoadTexture("nature_tileset/log.png");
    const Texture2D tGoblinIdle = LoadTexture("characters/goblin_idle_spritesheet.png");
    const Texture2D tGoblinRun = LoadTexture("characters/goblin_run_spritesheet.png");
#pragma endregion

    Character knight(tKnightIdle, tKnightRun);
    Prop props[2] = {
        Prop(Vector2{400.0f, 600.0f}, tRock),
        Prop(Vector2{600.0f, 400.0f}, tLog)};

    Enemy goblin(tGoblinIdle, tGoblinRun, Vector2{400.0f, 400.0f});

    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();
        knight.Tick(dt);

#pragma region Map Boundary Check
        Vector2 currentWorldPosition = knight.GetWorldPosition();
        if (currentWorldPosition.x < 0 ||
            currentWorldPosition.y < 0 ||
            currentWorldPosition.x > tGameMap.width * Config::kMapScale - Config::kScreenWidth ||
            currentWorldPosition.y > tGameMap.height * Config::kMapScale - Config::kScreenHeight)
        {
            knight.UndoMovement();
        }
#pragma endregion

        const Vector2 mapPosition = Vector2Scale(knight.GetWorldPosition(), -1.0f);
        for (Prop &p : props)
        {
            if (CheckCollisionRecs(knight.GetCollisionRectangle(), p.GetCollisionRectangle(mapPosition)))
            {
                knight.UndoMovement();
            }
        }

        goblin.Tick(dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(tGameMap, mapPosition, 0, Config::kMapScale, WHITE); // Draw the map
        for (const Prop &p : props)
        {
            p.Draw(mapPosition);
        }
        goblin.Draw();
        knight.Draw();
        EndDrawing();
    }
#pragma region Texture Unloading
    UnloadTexture(tGameMap);
    UnloadTexture(tKnightIdle);
    UnloadTexture(tKnightRun);
    UnloadTexture(tRock);
    UnloadTexture(tLog);
    UnloadTexture(tGoblinIdle);
    UnloadTexture(tGoblinRun);
#pragma endregion
    CloseWindow();
}
