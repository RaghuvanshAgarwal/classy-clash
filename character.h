#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(const Texture2D &idle_texture, const Texture2D &run_texture);
    virtual void Tick(float dt) override;
    virtual Rectangle GetCollisionRectangle() override;

private:
    /// @brief The Collision rectangle of the character
    Rectangle CollisionRectangle{};
};

#endif // CHARACTER_H
