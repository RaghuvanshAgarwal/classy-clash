#include "prop.h"
#include "config.h"
#include "raymath.h"

prop::prop(Vector2 pos, Texture2D text) : world_pos_(pos), texture_(text)
{
    scale_ = config::map_scale;
}

void prop::draw(Vector2 knight_pos) const
{
    Vector2 screen_pos = Vector2Add(world_pos_, knight_pos);
    DrawTextureEx(texture_, screen_pos, 0, scale_, WHITE);
}