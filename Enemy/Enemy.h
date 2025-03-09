#pragma once
#include "../BaseCharacter/BaseCharacter.h"
#include "../Character/Character.h"
#include "raylib.h"

class Enemy : public BaseCharacter {
public:
	Enemy(const Texture2D& idleTexture, const Texture2D& runTexture, Vector2 pos);
	virtual void Tick(float dt) override;
	virtual void Draw() const override;
	void SetTarget(Character* target) { Target = target; }
	virtual Vector2 GetScreenPosition() const override;

private:
	void FollowPlayer();
	Character* Target;
	float DamagePerSecond{ 10.0f };
};
