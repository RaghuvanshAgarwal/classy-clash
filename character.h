#include "raylib.h"

class character
{
public:
    character(const Texture2D& idle_texture, const Texture2D& run_texture);
    Vector2 get_world_pos() const { return world_pos_; }
    void undo_movement();
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
    Vector2 last_world_pos_{};

    float right_left_{1.0f};
    float running_time_{0.0f};
    int frame_{0};
    float width_{0.0f};
    float height_{0.0f};
};