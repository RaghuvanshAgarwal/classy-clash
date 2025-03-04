#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 pos);
    virtual void Tick(float dt) override;
};

#endif // ENEMY_H