#pragma once  
#include "raylib.h"  
#include "../BaseCharacter/BaseCharacter.h"

class Character : public BaseCharacter  
{  
public:  
   Character(const Texture2D& idleTexture, const Texture2D& runTexture);  
   virtual void Tick(float dt) override;  
   virtual Rectangle GetCollisionRectangle() override;  
   virtual Vector2 GetScreenPosition() const override;  

private:  
   /// @brief The Collision rectangle of the character  
   Rectangle CollisionRectangle{};  
};