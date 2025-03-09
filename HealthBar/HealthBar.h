#pragma once
#include "raylib.h"
class HealthBar {
public:
	HealthBar(Rectangle rect);
	void Draw(float currentHealth, float maxHealth) const;
private:
	Rectangle Rect;
};