#pragma once
#include "Enemy.h"

#include <iostream>

#include "../Config.h"
#include "raylib.h"
#include "raymath.h"

Enemy::Enemy(const Texture2D& idleTexture, const Texture2D& runTexture,
	Vector2 pos)
	: BaseCharacter(idleTexture, runTexture) {
	WorldPosition = pos;
	Target = nullptr;
}

void Enemy::Tick(float dt) {
	if (!GetIsAlive() || !Target->GetIsAlive()) return;
	LastWorldPosition = WorldPosition;
	MoveDirection = Vector2Zero();
	if (Vector2Distance(GetScreenPosition(), Target->GetScreenPosition()) > TargetMinDistance)
	{
		FollowPlayer();
	}
	else {
		bRandomOffsetCalculated = false;
	}
	BaseCharacter::Tick(dt);
	if (CheckCollisionRecs(GetCollisionRectangle(), Target->GetCollisionRectangle()) && Target->GetIsAlive())
	{
		Target->TakeDamage(DamagePerSecond * dt);
	}
}

void Enemy::FollowPlayer() {
	if (!bRandomOffsetCalculated) {
		bRandomOffsetCalculated = true;
		RandomOffset = { 
			static_cast<float>(GetRandomValue(-TargetMinDistance, TargetMinDistance)), 
			static_cast<float>(GetRandomValue(-TargetMinDistance, TargetMinDistance)),
		};
	}
	MoveDirection =
		Vector2Subtract(Target->GetScreenPosition() + RandomOffset, GetScreenPosition());
	const Vector2 directionNormalized = Vector2Normalize(MoveDirection);
	const Vector2 deltaThisFrame =
		Vector2Scale(directionNormalized, Speed * GetFrameTime());
	WorldPosition = Vector2Add(WorldPosition, deltaThisFrame);
}

Vector2 Enemy::GetScreenPosition() const {
	return Vector2Subtract(WorldPosition, Target->GetWorldPosition());
}

void Enemy::Draw() const {
	if (!GetIsAlive()) return;
	BaseCharacter::Draw();
}
