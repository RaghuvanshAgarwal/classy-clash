#pragma once
#include "../BaseCharacter/BaseCharacter.h"
#include "raylib.h"

class Character : public BaseCharacter {
public:
	Character(const Texture2D& idleTexture, const Texture2D& runTexture);
	virtual void Tick(float dt) override;
	virtual void Draw() const override;
	virtual Rectangle GetCollisionRectangle() override;
	virtual Vector2 GetScreenPosition() const override;
	void SetSwordTexture(Texture* texture) { tSwordTexture = texture; }
	const Rectangle* GetSwordCollisionRectangle() const { return &SwordCollisionRectangle; }

private:
	void DrawSword() const;

	/// @brief The Collision rectangle of the character
	Rectangle CollisionRectangle{};
	Texture* tSwordTexture;
	Vector2 SwordOffset{};
	Vector2 SwordOrigin{};
	float SwordRotation{};
	Rectangle SwordCollisionRectangle{};

};