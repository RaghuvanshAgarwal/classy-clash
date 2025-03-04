#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    virtual void Tick(float dt);
    virtual Rectangle GetCollisionRectangle();
    Vector2 GetWorldPosition() const { return WorldPosition; }
    void UndoMovement();
    void Draw() const;
    

protected:
    /// @brief The update time of the character
    float UpdateTime{1.0f / 12.0f};
    /// @brief The max frame of the character
    int MaxFrame{6};
    /// @brief The speed of the character
    float Speed{400.0f};

    /// @brief The current active texture
    Texture2D CurrentTexture{};
    /// @brief The stored idle animation texture
    Texture2D IdleTexture{};
    /// @brief The stored run animation texture
    Texture2D RunTexture{};
    /// @brief The world position of the character
    Vector2 WorldPosition{};
    /// @brief The screen position of the character
    Vector2 ScreenPosition{};
    /// @brief The last world position of the character
    Vector2 LastWorldPosition{};
    /// @brief The right left direction of the character
    float FacingDirection{1.0f};
    /// @brief The running time of the character
    float RunningTime{0.0f};
    /// @brief The frame of the character
    int CurrentFrameIndex{0};
    /// @brief The width of the character
    float Width{0.0f};
    /// @brief The height of the character
    float Height{0.0f};
};

#endif // BASE_CHARACTER_H
