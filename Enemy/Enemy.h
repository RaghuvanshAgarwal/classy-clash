#pragma once
#include "raylib.h"
#include "../BaseCharacter/BaseCharacter.h"
#include "../Character/Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(const Texture2D& idleTexture, const Texture2D& runTexture, Vector2 pos);
    virtual void Tick(float dt) override;
    void SetTarget(Character* target) { Target = target; }
    virtual Vector2 GetScreenPosition() const override;

private:
    void FollowPlayer();
    Character* Target;
};

