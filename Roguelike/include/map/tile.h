#pragma once
#include "graphics\tileset.h"
#include "collision\aabb.h"

class Tile
{
public:

	Tile(AABB hitbox);
	Tile(AABB hitbox, Tileset background);
	Tile(AABB hitbox, Tileset background, json tilesetData);

	void SetBackgroundSprite(Tileset sprite);
	void SetOverlaySprite(Tileset sprite);
	void SetForegroundSprite(Tileset sprite);

	Tileset& GetBackgroundSprite();
	Tileset& GetOverlaySprite();
	Tileset& GetForegroundSprite();

	Vector2f GetPosition() const;
	const AABB& GetHitbox() const;

	void Draw(RenderWindow& window);

	bool IsSolid() const;

private:

	Tileset background;
	Tileset overlay;
	Tileset foreground;
	
	bool isVisible = true;
	bool overlayIsVisible = false;
	bool foregroundIsVisible = false;

	AABB hitbox;

	bool isSolid = false;
};