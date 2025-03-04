#include "raylib.h"
#include "raymath.h"
#include "Enemy.h"
#include "Config.h"

Enemy::Enemy(const Texture2D &idle_texture, const Texture2D &run_texture, Vector2 pos) : BaseCharacter(idle_texture, run_texture)
{
}

void Enemy::Tick(float dt)
{
    LastWorldPosition = WorldPosition;
    BaseCharacter::Tick(dt);
}
