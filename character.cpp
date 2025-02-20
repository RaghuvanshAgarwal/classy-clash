#include "character.h"
#include "raymath.h"
#include "config.h"

/// @brief Constructor for the character class
/// @param idle_texture The idle texture for the character
/// @param run_texture The run texture for the character
character::character(const Texture2D& idle_texture, const Texture2D& run_texture)
{
    idle_texture_ = idle_texture;
    run_texture_ = run_texture;
    texture_ = idle_texture_;
    width_ = config::map_scale * static_cast<float>(texture_.width) / max_frame_;
    height_ = config::map_scale * static_cast<float>(texture_.height);

    screen_pos_ = {
        static_cast<float>(config::screen_width) / 2.0f - 0.5f * width_,
        static_cast<float>(config::screen_height) / 2.0f - 0.5f * height_
    };

    collison_rect_ = {
        screen_pos_.x,
        screen_pos_.y,
        width_,
        height_
    };
}

/// @brief Undo the movement of the character
void character::undo_movement()
{
    world_pos_ = last_world_pos_;
}

/// @brief Tick the character
/// @param dt The delta time
void character::tick(const float dt)
{
    last_world_pos_ = world_pos_;
    Vector2 direction{0.0f, 0.0f};
    if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
    if (IsKeyDown(KEY_D)) direction.x += 1.0f;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
    if (IsKeyDown(KEY_S)) direction.y += 1.0f;

    if (Vector2Length(direction) > 0.0f)
    {
        right_left_ = direction.x != 0.0f ? direction.x < 0.f ? -1.0f : 1.0f : right_left_;
        world_pos_ = Vector2Add(world_pos_, Vector2Scale(Vector2Normalize(direction), speed_ * dt));
        texture_ = run_texture_;
    }
    else
    {
        texture_ = idle_texture_;
    }

    running_time_ += dt;
    if (running_time_ >= update_time_)
    {
        frame_ = (frame_ + 1) % max_frame_;
        running_time_ = 0.0f;
    }
}

/// @brief Draw the character
void character::draw() const
{
    const Rectangle knight_source_rect{
        static_cast<float>(frame_) * static_cast<float>(texture_.width) / 6.0f,
        0,
        right_left_ * static_cast<float>(texture_.width) / 6.0f,
        static_cast<float>(texture_.height)
    };

    const Rectangle knight_dest_rect{
        screen_pos_.x,
        screen_pos_.y,
        width_,
        height_
    };

    DrawTexturePro(texture_, knight_source_rect, knight_dest_rect, Vector2Zero(), 0,WHITE);
}
