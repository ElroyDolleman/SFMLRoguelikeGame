#include "map\tile.h"
#include "stdafx.h"

Tile::Tile(IntRect hitbox)
{
	isVisible = false;
}

Tile::Tile(IntRect hitbox, SpriteSheet background)
	: background(background)
{
	background.setPosition((float)hitbox.left, (float)hitbox.top);
}

void Tile::SetBackgroundSprite(SpriteSheet sprite)
{
	background = sprite;
	background.setPosition((float)hitbox.left, (float)hitbox.top);
	isVisible = true;
}

void Tile::SetOverlaySprite(SpriteSheet sprite)
{
	overlay = sprite;
	overlay.setPosition((float)hitbox.left, (float)hitbox.top);
	overlayIsVisible = true;
}

void Tile::SetForegroundSprite(SpriteSheet sprite)
{
	foreground = sprite;
	foreground.setPosition((float)hitbox.left, (float)hitbox.top);
	foregroundIsVisible = true;
}

SpriteSheet& Tile::GetBackgroundSprite()
{
	return background;
}

SpriteSheet& Tile::GetOverlaySprite()
{
	return overlay;
}

SpriteSheet& Tile::GetForegroundSprite()
{
	return foreground;
}

Vector2f Tile::GetPosition() const
{
	return Vector2f((float)hitbox.left, (float)hitbox.top);
}

const IntRect & Tile::GetHitbox() const
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