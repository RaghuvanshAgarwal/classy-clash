#include "raylib.h"

class prop
{
public:
    prop(Vector2 pos, Texture2D tex);

private:
    Texture2D texture_{};
    Vector2 world_pos_{};
    float scale_{};
};