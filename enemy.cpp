#include "raylib.h"
#include "raymath.h"
#include "Enemy.h"
#include "Config.h"

Enemy::Enemy(Texture2D idle, Texture2D run, Vector2 pos) : CurrentTexture(idle), IdleTexture(idle), RunTexture(run), WorldPosition(pos)
{
    Width = Config::kMapScale * static_cast<float>(CurrentTexture.width) / MaxFrame;
    Height = Config::kMapScale * static_cast<float>(CurrentTexture.height);
}

void Enemy::UndoMovement()
{
    WorldPosition = LastWorldPosition;
}

void Enemy::Tick(float dt)
{
    LastWorldPosition = WorldPosition;
    RunningTime += dt;
    if (RunningTime >= UpdateTime)
    {
        CurrentFrame = (CurrentFrame + 1) % MaxFrame;
        RunningTime = 0.0f;
    }
}

void Enemy::Draw() const
{
    const Rectangle source{
        static_cast<float>(CurrentFrame) * static_cast<float>(CurrentTexture.width) / 6.0f,
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

Rectangle Enemy::GetCollisionRectangle() const
{
    return Rectangle{
        ScreenPosition.x,
        ScreenPosition.y,
        Width,
        Height};
}