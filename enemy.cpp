#include "raylib.h"
#include "raymath.h"
#include "enemy.h"
#include "config.h"

enemy::enemy(Texture2D idle, Texture2D run, Vector2 pos) : texture_(idle), idle_texture_(idle), run_texture_(run), world_pos_(pos)
{
    width_ = config::map_scale * static_cast<float>(texture_.width) / max_frame_;
    height_ = config::map_scale * static_cast<float>(texture_.height);
}

void enemy::undo_movement()
{
    world_pos_ = last_world_pos_;
}

void enemy::tick(float dt)
{
    last_world_pos_ = world_pos_;
    running_time_ += dt;
    if (running_time_ >= update_time_)
    {
        frame_ = (frame_ + 1) % max_frame_;
        running_time_ = 0.0f;
    }
}

void enemy::draw() const
{
    const Rectangle source{
        static_cast<float>(frame_) * static_cast<float>(texture_.width) / 6.0f,
        0,
        right_left_ * static_cast<float>(texture_.width) / 6.0f,
        static_cast<float>(texture_.height)};

    const Rectangle dest{
        screen_pos_.x,
        screen_pos_.y,
        width_,
        height_};

    DrawTexturePro(texture_, source, dest, Vector2Zero(), 0, WHITE);
}

Rectangle enemy::get_collision_rect() const
{
    return Rectangle{
        screen_pos_.x,
        screen_pos_.y,
        width_,
        height_};
}