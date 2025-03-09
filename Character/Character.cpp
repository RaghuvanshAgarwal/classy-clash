#pragma once
#include "Character.h"

#include "../Config.h"
#include "raymath.h"

/// @brief Constructor for the character class
/// @param idleTexture The idle texture for the character
/// @param runTexture The run texture for the character
Character::Character(const Texture2D& idleTexture, const Texture2D& runTexture)
	: BaseCharacter(idleTexture, runTexture) {
	CollisionRectangle = {
		GetScreenPosition().x,
		GetScreenPosition().y,
		Width,
		Height,
	};
	tSwordTexture = nullptr;
}

/// @brief Tick the character
/// @param dt The delta time
void Character::Tick(const float dt) {
	if (!GetIsAlive()) return;
	LastWorldPosition = WorldPosition;
	MoveDirection = { 0.0f, 0.0f };
	if (IsKeyDown(KEY_A)) MoveDirection.x -= 1.0f;
	if (IsKeyDown(KEY_D)) MoveDirection.x += 1.0f;
	if (IsKeyDown(KEY_W)) MoveDirection.y -= 1.0f;
	if (IsKeyDown(KEY_S)) MoveDirection.y += 1.0f;

	BaseCharacter::Tick(dt);

	if (FacingDirection > 0.0f) {
		SwordOrigin = { 0.0f, tSwordTexture->height * Config::kMapScale };
		SwordOffset = { 40,55 };
		SwordCollisionRectangle = {
			GetScreenPosition().x + SwordOffset.x,
			GetScreenPosition().y + SwordOffset.y - tSwordTexture->height * Config::kMapScale,
			tSwordTexture->width * Config::kMapScale,
			tSwordTexture->height * Config::kMapScale,
		};
		SwordRotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.0f : 0.0f;
	}
	else {
		SwordOrigin = { tSwordTexture->width * Config::kMapScale,
					   tSwordTexture->height * Config::kMapScale };
		SwordOffset = { 20,55 };
		SwordCollisionRectangle = {
			GetScreenPosition().x + SwordOffset.x - tSwordTexture->width * Config::kMapScale,
			GetScreenPosition().y + SwordOffset.y - tSwordTexture->height * Config::kMapScale,
			tSwordTexture->width * Config::kMapScale,
			tSwordTexture->height * Config::kMapScale,
		};
		SwordRotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.0f : 0.0f;
	}
}

Rectangle Character::GetCollisionRectangle() { return CollisionRectangle; }

Vector2 Character::GetScreenPosition() const {
	return {
		static_cast<float>(Config::kScreenWidth) / 2.0f - 0.5f * Width,
		static_cast<float>(Config::kScreenHeight) / 2.0f - 0.5f * Height,
	};
}

void Character::Draw() const {
	if (!GetIsAlive()) return;
	BaseCharacter::Draw();
	DrawSword();
}

void Character::DrawSword() const {
	Rectangle source = {
		0,
		0,
		static_cast<float>(tSwordTexture->width * FacingDirection),
		static_cast<float>(tSwordTexture->height),
	};
	Rectangle dest = {
		GetScreenPosition().x + SwordOffset.x,
		GetScreenPosition().y + SwordOffset.y,
		tSwordTexture->width * Config::kMapScale,
		tSwordTexture->height * Config::kMapScale,
	};

	DrawTexturePro(*tSwordTexture, source, dest, SwordOrigin, SwordRotation, WHITE);
	/*DrawRectangleLines(static_cast<int>(SwordCollisionRectangle.x), static_cast<int>(SwordCollisionRectangle.y),
		static_cast<int>(SwordCollisionRectangle.width), static_cast<int>(SwordCollisionRectangle.height),
		RED);*/
}
