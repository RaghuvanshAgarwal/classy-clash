#pragma once
#include "Character.h"
#include "raymath.h"
#include "../Config.h"

/// @brief Constructor for the character class
/// @param idleTexture The idle texture for the character
/// @param runTexture The run texture for the character
Character::Character(const Texture2D& idleTexture, const Texture2D& runTexture) : BaseCharacter(idleTexture, runTexture)
{
    CollisionRectangle = {
        GetScreenPosition().x,
        GetScreenPosition().y,
        Width,
        Height,
    };
}

/// @brief Tick the character
/// @param dt The delta time
void Character::Tick(const float dt)
{
    LastWorldPosition = WorldPosition;
    MoveDirection = { 0.0f, 0.0f };
    if (IsKeyDown(KEY_A))
        MoveDirection.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        MoveDirection.x += 1.0f;
    if (IsKeyDown(KEY_W))
        MoveDirection.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        MoveDirection.y += 1.0f;

    BaseCharacter::Tick(dt);
}

Rectangle Character::GetCollisionRectangle()
{
    return CollisionRectangle;
}

#include "../Config.h" // Add this include at the top of the file

Vector2 Character::GetScreenPosition() const
{
   return {
       static_cast<float>(Config::kScreenWidth) / 2.0f - 0.5f * Width,
       static_cast<float>(Config::kScreenHeight) / 2.0f - 0.5f * Height,
   };
}
