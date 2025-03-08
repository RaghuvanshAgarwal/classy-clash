#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Enemy.h"
#include "../Config.h"
#include <iostream>

Enemy::Enemy(const Texture2D& idleTexture, const Texture2D& runTexture, Vector2 pos) : BaseCharacter(idleTexture, runTexture)
{
    WorldPosition = pos;
}

void Enemy::Tick(float dt)
{
    LastWorldPosition = WorldPosition;
    MoveDirection = Vector2Zero();
    if (Vector2Distance(GetScreenPosition(), Target->GetScreenPosition()) > 70)
    {
        FollowPlayer();
    }
    BaseCharacter::Tick(dt);
}

void Enemy::FollowPlayer()
{
    MoveDirection = Vector2Subtract(Target->GetScreenPosition(), GetScreenPosition());
    const Vector2 directionNormalized = Vector2Normalize(MoveDirection);
    const Vector2 deltaThisFrame = Vector2Scale(directionNormalized, Speed * GetFrameTime());
    WorldPosition = Vector2Add(WorldPosition, deltaThisFrame);
}

Vector2 Enemy::GetScreenPosition() const
{
    return Vector2Subtract(WorldPosition, Target->GetWorldPosition());
}
