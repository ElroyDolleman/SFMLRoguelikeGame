#include "stdafx.h"
#include "map\tile.h"

Tile::Tile(AABB hitbox)
	: hitbox(hitbox)
{
	isVisible = false;
}

Tile::Tile(AABB hitbox, Tileset background)
	: hitbox(hitbox)
{
	SetBackgroundSprite(background);
}

Tile::Tile(AABB hitbox, Tileset background, json tilesetData)
	: Tile(hitbox, background)
{
#if _DEBUG
	if (tilesetData["tileproperties"][to_string(background.getTileNumber())]["solid"].is_null())
	{
		printf("Warning: Failed to get the isSolid property from tile number %i.\n", background.getTileNumber());
		return;
	}
#endif
	isSolid = tilesetData["tileproperties"][to_string(background.getTileNumber())]["solid"].get<bool>();
}

void Tile::SetBackgroundSprite(Tileset sprite)
{
	background = sprite;
	background.setPosition((float)hitbox.left, (float)hitbox.top);
	isVisible = true;
}

void Tile::SetOverlaySprite(Tileset sprite)
{
	overlay = sprite;
	overlay.setPosition((float)hitbox.left, (float)hitbox.top);
	overlayIsVisible = true;
}

void Tile::SetForegroundSprite(Tileset sprite)
{
	foreground = sprite;
	foreground.setPosition((float)hitbox.left, (float)hitbox.top);
	foregroundIsVisible = true;
}

Tileset& Tile::GetBackgroundSprite()
{
	return background;
}

Tileset& Tile::GetOverlaySprite()
{
	return overlay;
}

Tileset& Tile::GetForegroundSprite()
{
	return foreground;
}

Vector2f Tile::GetPosition() const
{
	return Vector2f((float)hitbox.left, (float)hitbox.top);
}

const AABB& Tile::GetHitbox() const
{
	return hitbox;
}

void Tile::Draw(RenderWindow& window)
{
	if (!isVisible)
		return;

	window.draw(background);

	if (overlayIsVisible)
		window.draw(overlay);

	if (foregroundIsVisible)
		window.draw(foreground);
}

bool Tile::IsSolid() const
{
	return isSolid;
}
