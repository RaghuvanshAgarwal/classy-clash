#include "prop.h"

prop::prop(Vector2 pos, Texture2D text) : world_pos_(pos), texture_(text)
{
    scale_ = 1.0f;
}