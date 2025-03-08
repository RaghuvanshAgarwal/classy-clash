#pragma once
#include "BaseCharacter.h"
#include "raymath.h"
#include "../Config.h"

BaseCharacter::BaseCharacter(const Texture2D& idleTexture, const Texture2D& runTexture)
{
    IdleTexture = idleTexture;
    RunTexture = runTexture;
    CurrentTexture = idleTexture;
    Width = Config::kMapScale * static_cast<float>(CurrentTexture.width) / MaxFrame;
    Height = Config::kMapScale * static_cast<float>(CurrentTexture.height);
}

void BaseCharacter::UndoMovement()
{
    WorldPosition = LastWorldPosition;
}

void BaseCharacter::Tick(float dt)
{
    if (Vector2Length(MoveDirection) != 0.0f)
    {
        CurrentTexture = RunTexture;
        const Vector2 directionNormalized = Vector2Normalize(MoveDirection);
        FacingDirection = directionNormalized.x != 0.0f ? directionNormalized.x < 0.f ? -1.0f : 1.0f : FacingDirection;
        WorldPosition = Vector2Add(WorldPosition, Vector2Scale(directionNormalized, Speed * dt));
    }
    else
    {
        CurrentTexture = IdleTexture;
    }

    RunningTime += dt;
    if (RunningTime >= UpdateTime)
    {
        CurrentFrameIndex = (CurrentFrameIndex + 1) % MaxFrame;
        RunningTime = 0.0f;
    }
}

void BaseCharacter::Draw() const
{
    const Rectangle source{
        static_cast<float>(CurrentFrameIndex) * static_cast<float>(CurrentTexture.width) / 6.0f,
        0,
        FacingDirection * static_cast<float>(CurrentTexture.width) / 6.0f,
        static_cast<float>(CurrentTexture.height) };
    const Vector2 screenPosition = GetScreenPosition();
    const Rectangle dest{
        screenPosition.x,
        screenPosition.y,
        Width,
        Height };

    DrawTexturePro(CurrentTexture, source, dest, Vector2Zero(), 0, WHITE);
}

Rectangle BaseCharacter::GetCollisionRectangle()
{
    const Vector2 screenPosition = GetScreenPosition();
    return Rectangle{
        screenPosition.x,
        screenPosition.y,
        Width,
        Height,
    };
}
