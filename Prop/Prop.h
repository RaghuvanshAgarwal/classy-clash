#pragma once
#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Draw(Vector2 map_pos) const;
    Rectangle GetCollisionRectangle(const Vector2 map_pos) const;

private:
    Vector2 WorldPosition;
    Texture2D Texture;
    float Scale{};
};