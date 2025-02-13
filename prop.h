#include "raylib.h"

class prop
{
public:
    prop(Vector2 pos, Texture2D tex);
    void draw(Vector2 knight_pos) const;

private:
    Vector2 world_pos_;
    Texture2D texture_;
    float scale_{};
};