#pragma once
#include "stdafx.h"

class Tile
{
public:

	Tile(IntRect hitbox, Sprite background);

	void SetBackgroundSprite(sf::Sprite sprite);
	void SetOverlaySprite(sf::Sprite sprite);
	void SetForegroundSprite(sf::Sprite sprite);

	Sprite& GetBackgroundSprite();
	Sprite& GetOverlaySprite();
	Sprite& GetForegroundSprite();

	Vector2f GetPosition() const;
	const IntRect& GetHitbox() const;

private:

	Sprite background;
	Sprite overlay;
	Sprite foreground;

	IntRect hitbox;
};