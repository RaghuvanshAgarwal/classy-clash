#include "prop.h"
#include "Config.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D text) : WorldPosition(pos), Texture(text)
{
    Scale = Config::kMapScale;
}

void Prop::Draw(Vector2 map_pos) const
{
    Vector2 screen_pos = Vector2Add(WorldPosition, map_pos);
    DrawTextureEx(Texture, screen_pos, 0, Scale, WHITE);
}

Rectangle Prop::GetCollisionRectangle(const Vector2 map_pos) const
{
    Vector2 screen_pos = Vector2Add(WorldPosition, map_pos);
    return Rectangle{
        screen_pos.x,
        screen_pos.y,
        static_cast<float>(Texture.width) * Scale,
        static_cast<float>(Texture.height) * Scale};
}