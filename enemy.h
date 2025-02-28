#include "raylib.h"


class enemy {
public:
    enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 pos);
    Vector2 get_world_pos() const { return world_pos_; }
    Rectangle get_collision_rect() const;
    void undo_movement();
    void tick(float dt);
    void draw() const;

private:
    /// @brief The update time of the character
    float update_time_{1.0f / 12.0f};
    /// @brief The max frame of the character
    int max_frame_{6};
    /// @brief The speed of the character
    float speed_{400.0f};

    /// @brief The current active texture
    Texture2D texture_{};
    /// @brief The stored idle animation texture
    Texture2D idle_texture_{};
    /// @brief The stored run animation texture
    Texture2D run_texture_{};
    /// @brief The world position of the character
    Vector2 world_pos_{};
    /// @brief The screen position of the character
    Vector2 screen_pos_{};
    /// @brief The last world position of the character
    Vector2 last_world_pos_{};
    /// @brief The right left direction of the character
    float right_left_{1.0f};
    /// @brief The running time of the character
    float running_time_{0.0f};
    /// @brief The frame of the character
    int frame_{0};
    /// @brief The width of the character
    float width_{0.0f};
    /// @brief The height of the character
    float height_{0.0f};
};