#include <iostream>

#include "Character/Character.h"
#include "Config.h"
#include "Enemy/Enemy.h"
#include "Prop/Prop.h"
#include "HealthBar/HealthBar.h"
#include "raylib.h"
#include "raymath.h"

int main() {
	InitWindow(Config::kScreenWidth, Config::kScreenHeight, "Classy Clash");
	SetTargetFPS(60);

#pragma region Texture Loading
	const Texture2D tGameMap = LoadTexture("nature_tileset/game-map_v2.png");
	const Texture2D tKnightIdle =
		LoadTexture("characters/knight_idle_spritesheet.png");
	const Texture2D tKnightRun =
		LoadTexture("characters/knight_run_spritesheet.png");
	const Texture2D tRock = LoadTexture("nature_tileset/rock.png");
	const Texture2D tLog = LoadTexture("nature_tileset/log.png");
	const Texture2D tGoblinIdle =
		LoadTexture("characters/goblin_idle_spritesheet.png");
	const Texture2D tGoblinRun =
		LoadTexture("characters/goblin_run_spritesheet.png");
	const Texture2D tSword = LoadTexture("characters/weapon_sword.png");
	const Texture2D tSlimeIdle =
		LoadTexture("characters/slime_idle_spritesheet.png");
	const Texture2D tSlimeRun =
		LoadTexture("characters/slime_run_spritesheet.png");
#pragma endregion

	Character knight(tKnightIdle, tKnightRun);
	HealthBar healthBar(Rectangle{ 10, 10, 100, 20 });
	knight.SetSwordTexture(const_cast<Texture*>(&tSword));
	Prop props[2] = { Prop(Vector2{400.0f, 600.0f}, tRock),
					 Prop(Vector2{600.0f, 400.0f}, tLog) };

	Enemy goblin(tGoblinIdle, tGoblinRun, Vector2{ 400.0f, 400.0f });
	Enemy slime(tSlimeIdle, tSlimeRun, Vector2{ 600.0f, 600.0f });
	Enemy* enemies[2] = { &goblin, &slime };
	for (Enemy* enemy : enemies) {
		enemy->SetTarget(&knight);
		enemy->SetSpeed(150.0f);
	}

	while (!WindowShouldClose()) {
		const float dt = GetFrameTime();
		knight.Tick(dt);

#pragma region Map Boundary Check
		Vector2 currentWorldPosition = knight.GetWorldPosition();
		if (currentWorldPosition.x < 0 || currentWorldPosition.y < 0 ||
			currentWorldPosition.x >
			tGameMap.width * Config::kMapScale - Config::kScreenWidth ||
			currentWorldPosition.y >
			tGameMap.height * Config::kMapScale - Config::kScreenHeight) {
			knight.UndoMovement();
		}
#pragma endregion

		const Vector2 mapPosition = Vector2Scale(knight.GetWorldPosition(), -1.0f);
		for (Prop& p : props) {
			if (CheckCollisionRecs(knight.GetCollisionRectangle(),
				p.GetCollisionRectangle(mapPosition))) {
				knight.UndoMovement();
			}
		}

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			for (Enemy* enemy : enemies) {
				if (CheckCollisionRecs(*knight.GetSwordCollisionRectangle(), enemy->GetCollisionRectangle())) {
					enemy->SetIsAlive(false);
				}
			}
		}

		for (Enemy* enemy : enemies) {
			enemy->Tick(dt);
		}
		

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTextureEx(tGameMap, mapPosition, 0, Config::kMapScale,
			WHITE);  // Draw the map
		for (const Prop& p : props) {
			p.Draw(mapPosition);
		}
		for (Enemy* enemy : enemies) {
			enemy->Draw();
		}
		if (knight.GetIsAlive()) {
			knight.Draw();
			healthBar.Draw(knight.GetCurrentHealth(), knight.GetMaxHealth());
		}
		else {
			int offset = MeasureText("Game Over", 40);
			DrawText("Game Over", Config::kScreenWidth / 2 - offset / 2,
				Config::kScreenHeight / 2 - 40, 40, RED);
		}
		
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
	UnloadTexture(tSword);
	UnloadTexture(tSlimeIdle);
	UnloadTexture(tSlimeRun);
#pragma endregion
	CloseWindow();
}
