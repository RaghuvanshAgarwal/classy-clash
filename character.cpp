#include "character.h"
#include "raymath.h"


character::character(const Texture2D& idle_texture, const Texture2D& run_texture,  float map_scale)
{
    idle_texture_ = idle_texture;
    run_texture_ = run_texture;
    texture_ = idle_texture_;
    width_ = map_scale * static_cast<float>(texture_.width) / max_frame_;
    height_ = map_scale * static_cast<float>(texture_.height);
    map_scale_ = map_scale;
}


void character::set_screen_pos(const int win_width, const int win_height)
{
    screen_pos_ = {
        static_cast<float>(win_width) / 2.0f - map_scale_ * 0.5f * static_cast<float>(texture_.width) / max_frame_,
        static_cast<float>(win_height) / 2.0f - map_scale_ * 0.5f * static_cast<float>(texture_.height)
    };
}

void character::undo_movement()
{
    world_pos_ = last_world_pos_;
}

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
