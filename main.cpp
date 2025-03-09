#include <iostream>
#include <string>
#include <cstdio>

#include "Character/Character.h"
#include "Config.h"
#include "Enemy/Enemy.h"
#include "Prop/Prop.h"
#include "HealthBar/HealthBar.h"
#include "raylib.h"
#include "raymath.h"
#include "main.h"


void CreateEnemyArray(Enemy* enemyArray[10], const Texture2D& tGoblinIdle, const Texture2D& tGoblinRun, const Texture2D& tSlimeIdle, const Texture2D& tSlimeRun, Character& knight)
{
	for (size_t i = 0; i < 10; i++)
	{
		Vector2 position = { GetRandomValue(0,2600), GetRandomValue(0,2600) };
		if (i % 2 == 0) {
			enemyArray[i] = new Enemy(tGoblinIdle, tGoblinRun, position);
		}
		else {
			enemyArray[i] = new Enemy(tSlimeIdle, tSlimeRun, position);
		}
		enemyArray[i]->SetTarget(&knight);
		enemyArray[i]->SetSpeed(150.0f);
	}
}

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

	Enemy* enemyArray[10];
	CreateEnemyArray(enemyArray, tGoblinIdle, tGoblinRun, tSlimeIdle, tSlimeRun, knight);
	int enemyKilled = 0;
	int waves = 0;

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
			for (Enemy* enemy : enemyArray) {
				if (CheckCollisionRecs(*knight.GetSwordCollisionRectangle(), enemy->GetCollisionRectangle())) {
					enemy->SetIsAlive(false);
					enemyKilled++;
				}
			}
		}

		for (Enemy* enemy : enemyArray) {
			enemy->Tick(dt);
		}

		bool allDead = true;
		for (Enemy* enemy : enemyArray) {
			if (enemy->GetIsAlive()) {
				allDead = false;
				break;
			}
		}
		if (allDead) {
			for (size_t i = 0; i < 10; i++)
			{
				enemyArray[i] = nullptr;
			}
			CreateEnemyArray(enemyArray, tGoblinIdle, tGoblinRun, tSlimeIdle, tSlimeRun, knight);
			waves++;
		}
		

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTextureEx(tGameMap, mapPosition, 0, Config::kMapScale,
			WHITE);  // Draw the map
		for (const Prop& p : props) {
			p.Draw(mapPosition);
		}
		for (Enemy* enemy : enemyArray) {
			enemy->Draw();
		}
		if (knight.GetIsAlive()) {
			knight.Draw();
			healthBar.Draw(knight.GetCurrentHealth(), knight.GetMaxHealth());
		}
		else {
            std::string gameOverText = "Game Over\nWaves Survived: " + std::to_string(waves) + "\nEnemies Killed: " + std::to_string(enemyKilled);
			const int fontSize = 30;
			int gameOffset = MeasureText(gameOverText.c_str(), fontSize);
			DrawText(gameOverText.c_str(), Config::kScreenWidth / 2 - gameOffset / 2,
				Config::kScreenHeight / 2 - fontSize, fontSize, RED);
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
