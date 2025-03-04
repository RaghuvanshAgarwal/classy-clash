#include "Character.h"
#include "raymath.h"
#include "Config.h"

/// @brief Constructor for the character class
/// @param idle_texture The idle texture for the character
/// @param run_texture The run texture for the character
Character::Character(const Texture2D &idle_texture, const Texture2D &run_texture)
{
    IdleTexture = idle_texture;
    RunTexture = run_texture;
    CurrentTexture = idle_texture;
    Width = Config::kMapScale * static_cast<float>(CurrentTexture.width) / MaxFrame;
    Height = Config::kMapScale * static_cast<float>(CurrentTexture.height);

    ScreenPosition = {
        static_cast<float>(Config::kScreenWidth) / 2.0f - 0.5f * Width,
        static_cast<float>(Config::kScreenHeight) / 2.0f - 0.5f * Height};

    CollisionRectangle = {
        ScreenPosition.x,
        ScreenPosition.y,
        Width,
        Height};
}

/// @brief Tick the character
/// @param dt The delta time
void Character::Tick(const float dt)
{
    LastWorldPosition = WorldPosition;
    Vector2 direction{0.0f, 0.0f};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0f;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0f;

    if (Vector2Length(direction) > 0.0f)
    {
        FacingDirection = direction.x != 0.0f ? direction.x < 0.f ? -1.0f : 1.0f : FacingDirection;
        WorldPosition = Vector2Add(WorldPosition, Vector2Scale(Vector2Normalize(direction), Speed * dt));
        CurrentTexture = RunTexture;
    }
    else
    {
        CurrentTexture = IdleTexture;
    }

    BaseCharacter::Tick(dt);
}

Rectangle Character::GetCollisionRectangle()
{
    return CollisionRectangle;
}
