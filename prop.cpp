#include "prop.h"
#include "config.h"
#include "raymath.h"

prop::prop(Vector2 pos, Texture2D text) : world_pos_(pos), texture_(text)
{
    scale_ = config::map_scale;
}

void prop::draw(Vector2 map_pos) const
{
    Vector2 screen_pos = Vector2Add(world_pos_, map_pos);
    DrawTextureEx(texture_, screen_pos, 0, scale_, WHITE);
}

Rectangle prop::get_collision_rect(const Vector2 map_pos) const
{
    Vector2 screen_pos = Vector2Add(world_pos_, map_pos);
    return Rectangle{
        screen_pos.x,
        screen_pos.y,
        static_cast<float>(texture_.width) * scale_,
        static_cast<float>(texture_.height) * scale_};
}