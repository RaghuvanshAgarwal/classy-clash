#pragma once
#include "HealthBar.h"
#include <string>

HealthBar::HealthBar(Rectangle rect) {
	Rect = rect;
}

void HealthBar::Draw(float currentHealth, float maxHealth) const {
	float normalizedHealth = currentHealth / maxHealth;
	std::string healthString = std::to_string(static_cast<int>(currentHealth)) + "/" + std::to_string(static_cast<int>(maxHealth));
	DrawRectangle(Rect.x, Rect.y, Rect.width, Rect.height, BLACK);
	int border = 2;
	Rectangle backgroundRect = {
		Rect.x + border,
		Rect.y + border,
		Rect.width - border * 2,
		Rect.height - border * 2
	};
	DrawRectangleRec(backgroundRect, RED);
	Rectangle healthRect = {
		backgroundRect.x,
		backgroundRect.y,
		backgroundRect.width * normalizedHealth,
		backgroundRect.height
	};
	DrawRectangleRec(healthRect, GREEN);
	int offset = MeasureText(healthString.c_str(), 5);
	DrawText(healthString.c_str(), Rect.x + ((Rect.width - offset) * 0.5f), Rect.y + (Rect.height * 0.5f) - 5, 5, WHITE);

}