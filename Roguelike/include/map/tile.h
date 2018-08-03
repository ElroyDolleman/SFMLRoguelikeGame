#pragma once
#include "graphics\tileset.h"

class Tile
{
public:

	Tile(IntRect hitbox);
	Tile(IntRect hitbox, Tileset background);
	Tile(IntRect hitbox, Tileset background, json tilesetData);

	void SetBackgroundSprite(Tileset sprite);
	void SetOverlaySprite(Tileset sprite);
	void SetForegroundSprite(Tileset sprite);

	Tileset& GetBackgroundSprite();
	Tileset& GetOverlaySprite();
	Tileset& GetForegroundSprite();

	Vector2f GetPosition() const;
	const IntRect& GetHitbox() const;

	void Draw(RenderWindow& window);

private:

	Tileset background;
	Tileset overlay;
	Tileset foreground;
	
	bool isVisible = true;
	bool overlayIsVisible = false;
	bool foregroundIsVisible = false;

	IntRect hitbox;

	bool isSolid = false;
};