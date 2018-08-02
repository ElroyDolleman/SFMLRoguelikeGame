#include "graphics\spritesheet.h"

SpriteSheet::SpriteSheet()
	: Sprite()
{
}

SpriteSheet::SpriteSheet(const Texture& texture, int sheetWidth, int sheetHeight, int tileWidth, int tileHeight)
	: Sprite(texture)
{
	sheetSize = { sheetWidth, sheetHeight };
	tileSize = { tileWidth, tileHeight };

	updateTextureRect();
}

SpriteSheet::SpriteSheet(const Texture& texture, const Vector2i& sheetSize, const Vector2i& tileSize)
	: Sprite(texture)
{
	this->sheetSize = sheetSize;
	this->tileSize = tileSize;

	updateTextureRect();
}

void SpriteSheet::setTileWidth(int width)
{
	tileSize.x = width;
	updateTextureRect();
}

void SpriteSheet::setTileHeight(int height)
{
	tileSize.y = height;
	updateTextureRect();
}

void SpriteSheet::setTileSize(const Vector2i& size)
{
	tileSize = size;
	updateTextureRect();
}

void SpriteSheet::setSheetWidth(int width)
{
	sheetSize.x = width;
	updateTextureRect();
}

void SpriteSheet::setSheetHeight(int height)
{
	sheetSize.y = height;
	updateTextureRect();
}

void SpriteSheet::setSheetSize(const Vector2i & size)
{
	sheetSize = size;
	updateTextureRect();
}

void SpriteSheet::setOffset(int offsetX, int offsetY)
{
	offset = {offsetX, offsetY};
	updateTextureRect();
}

void SpriteSheet::setOffset(const Vector2i& offset)
{
	this->offset = offset;
	updateTextureRect();
}

void SpriteSheet::setInterspace(int interspaceWidth, int interspaceHeight)
{
	interspace = { interspaceWidth, interspaceHeight };
	updateTextureRect();
}

void SpriteSheet::setInterspace(const Vector2i& interspace)
{
	this->interspace = interspace;
	updateTextureRect();
}

void SpriteSheet::setTileNumber(int n)
{
	tileNumber = n;
	updateTextureRect();
}

int SpriteSheet::getTileWidth() const
{
	return tileSize.x;
}

int SpriteSheet::getTileHeight() const
{
	return tileSize.y;
}

const Vector2i& SpriteSheet::getTileSize() const
{
	return tileSize;
}

int SpriteSheet::getSheetWidth() const
{
	return sheetSize.x;
}

int SpriteSheet::getSheetHeight() const
{
	return sheetSize.y;
}

const Vector2i& SpriteSheet::getSheetSize() const
{
	return sheetSize;
}

const Vector2i& SpriteSheet::getOffset() const
{
	return offset;
}

const Vector2i& SpriteSheet::getInterspace() const
{
	return interspace;
}

int SpriteSheet::getTileNumber() const
{
	return tileNumber;
}

void SpriteSheet::updateTextureRect()
{
	int tilesPerRow = sheetSize.x / (tileSize.x + interspace.x);

	IntRect newTextureRect = { 0, 0, tileSize.x, tileSize.y };

	newTextureRect.left = offset.x + tileNumber % tilesPerRow * (tileSize.x + interspace.x);
	newTextureRect.top = offset.y + (int)floor(tileNumber / tilesPerRow) * (tileSize.y + interspace.y);

	setTextureRect(newTextureRect);
}