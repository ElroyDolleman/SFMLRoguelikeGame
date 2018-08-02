#pragma once
#include "graphics\spritesheet.h"

class Tile
{
public:

	Tile(IntRect hitbox);
	Tile(IntRect hitbox, SpriteSheet background);

	void SetBackgroundSprite(SpriteSheet sprite);
	void SetOverlaySprite(SpriteSheet sprite);
	void SetForegroundSprite(SpriteSheet sprite);

	SpriteSheet& GetBackgroundSprite();
	SpriteSheet& GetOverlaySprite();
	SpriteSheet& GetForegroundSprite();

	Vector2f GetPosition() const;
	const IntRect& GetHitbox() const;

	void Draw(RenderWindow& window);

private:

	SpriteSheet background;
	SpriteSheet overlay;
	SpriteSheet foreground;
	
	bool isVisible = true;
	bool overlayIsVisible = false;
	bool foregroundIsVisible = false;

	IntRect hitbox;
};