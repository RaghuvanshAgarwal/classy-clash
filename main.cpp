// classy-clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"
#include "raymath.h"

constexpr int screen_width{384};
constexpr int screen_height{384};
constexpr int map_scale{4};

class character
{
public:
    Vector2 get_world_pos() const { return world_pos_; }
    void set_screen_pos(int win_width, int win_height);
    void set_map_pos(Vector2 min_map_pos, Vector2 max_map_pos);
    void set_textures(const Texture2D& idle_texture, const Texture2D& run_texture);
    void tick(float dt);
    void draw() const;

private:
    float update_time_{1.0f / 12.0f};
    int max_frame_{6};
    float speed_{400.0f};
    
    Texture2D texture_ {};      // Current active texture
    Texture2D idle_texture_ {}; // Stored idle animation texture
    Texture2D run_texture_ {};  // Stored run animation texture
    Vector2 world_pos_ {};
    Vector2 screen_pos_{};
    Vector2 min_map_pos_{};
    Vector2 max_map_pos_{};

    float right_left_{1.0f};
    float running_time_{0.0f};
    int frame_{0};
};

void character::set_screen_pos(const int win_width, const int win_height)
{
    screen_pos_ = {
        static_cast<float>(win_width) / 2.0f - 4.0f * 0.5f * static_cast<float>(texture_.width) / 6.0f,
        static_cast<float>(win_height) / 2.0f - 4.0f * 0.5f * static_cast<float>(texture_.height)
    };
}

void character::set_map_pos(const Vector2 min_map_pos, const Vector2 max_map_pos)
{
    min_map_pos_ = min_map_pos;
    max_map_pos_ = max_map_pos;
}

void character::set_textures(const Texture2D& idle_texture, const Texture2D& run_texture)
{
    idle_texture_ = idle_texture;
    run_texture_ = run_texture;
    texture_ = idle_texture_;
}

void character::tick(const float dt)
{
    Vector2 direction{0.0f, 0.0f};
    if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
    if (IsKeyDown(KEY_D)) direction.x += 1.0f;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
    if (IsKeyDown(KEY_S)) direction.y += 1.0f;

    if (Vector2Length(direction) > 0.0f)
    {
        right_left_ = direction.x != 0.0f ? direction.x < 0.f ? -1.0f : 1.0f : right_left_;
        world_pos_ = Vector2Add(world_pos_, Vector2Scale(Vector2Normalize(direction), speed_ * dt));
        world_pos_ = Vector2Clamp(world_pos_, min_map_pos_, max_map_pos_);
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
        map_scale * static_cast<float>(texture_.width) / 6.0f,
        map_scale * static_cast<float>(texture_.height)
    };

    DrawTexturePro(texture_, knight_source_rect, knight_dest_rect, Vector2Zero(), 0,WHITE);
}

int main()
{
    InitWindow(screen_width, screen_height, "Classy Clash");
    SetTargetFPS(60);


#pragma region Texture Loading
    const Texture2D t_game_map = LoadTexture("nature_tileset/game-map_v2.png");
    const Texture2D t_knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    const Texture2D t_knight_run = LoadTexture("characters/knight_run_spritesheet.png");
#pragma endregion

#pragma region Map Variables
    const Vector2 max_map_pos{
        static_cast<float>(t_game_map.width * map_scale - screen_width),
        static_cast<float>(t_game_map.height * map_scale - screen_height)
    };
    constexpr Vector2 min_map_pos{0, 0};
#pragma endregion


    character knight {};
    knight.set_screen_pos(screen_width, screen_height);
    knight.set_map_pos(min_map_pos, Vector2Scale(max_map_pos, 0.9785f));
    knight.set_textures(t_knight_idle, t_knight_run);

    
    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();
        knight.tick(dt);
        Vector2 map_pos = Vector2Scale(knight.get_world_pos(), -1.0f);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(t_game_map, map_pos, 0, map_scale, WHITE); // Draw the map
        knight.draw();
        EndDrawing();
    }
#pragma region Texture Unloading
    UnloadTexture(t_game_map);
    UnloadTexture(t_knight_idle);
    UnloadTexture(t_knight_run);
#pragma endregion
    CloseWindow();
}
