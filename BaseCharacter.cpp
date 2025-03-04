#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::UndoMovement()
{
    WorldPosition = LastWorldPosition;
}

void BaseCharacter::Tick(float dt)
{
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
        static_cast<float>(CurrentTexture.height)};

    const Rectangle dest{
        ScreenPosition.x,
        ScreenPosition.y,
        Width,
        Height};

    DrawTexturePro(CurrentTexture, source, dest, Vector2Zero(), 0, WHITE);
}

Rectangle BaseCharacter::GetCollisionRectangle()
{
    return Rectangle{
        ScreenPosition.x, +ScreenPosition.y,
        Width,
        Height};
}