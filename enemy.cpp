#include "raylib.h"
#include "raymath.h"
#include "Enemy.h"
#include "Config.h"

Enemy::Enemy(Texture2D idle, Texture2D run, Vector2 pos)
{
    CurrentTexture = idle;
    IdleTexture = idle;
    RunTexture = run;
    WorldPosition = pos;
    Width = Config::kMapScale * static_cast<float>(CurrentTexture.width) / MaxFrame;
    Height = Config::kMapScale * static_cast<float>(CurrentTexture.height);
}

void Enemy::Tick(float dt)
{
    LastWorldPosition = WorldPosition;
    BaseCharacter::Tick(dt);
}
