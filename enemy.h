#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(const Texture2D& idle_texture, const Texture2D& run_texture, Vector2 pos);
    virtual void Tick(float dt) override;
    void SetTarget(Character* target) { Target = target; }

private:
    Character *Target;
};

#endif // ENEMY_H