#include "stdafx.h"
#include "graphics\tileset.h"

Tileset::Tileset()
	: Sprite()
{
}

Tileset::Tileset(const Texture& texture, int sheetWidth, int sheetHeight, int tileWidth, int tileHeight)
	: Sprite(texture)
{
	imageSize = { sheetWidth, sheetHeight };
	tileSize = { tileWidth, tileHeight };

	updateTextureRect();
}

Tileset::Tileset(const Texture& texture, const Vector2i& sheetSize, const Vector2i& tileSize)
	: Sprite(texture)
{
	this->imageSize = sheetSize;
	this->tileSize = tileSize;

	updateTextureRect();
}

Tileset::Tileset(const Texture& texture, const json& sheetData)
	: Sprite(texture)
{
	imageSize = { sheetData["imagewidth"].get<int>(), sheetData["imageheight"].get<int>() };
	tileSize = { sheetData["tilewidth"].get<int>(), sheetData["tileheight"].get<int>() };

	int s = sheetData["spacing"].get<int>();
	spacing = { s, s };

	int m = sheetData["margin"].get<int>();
	margin = { m, m };
}

void Tileset::setTileWidth(int width)
{
	tileSize.x = width;
	updateTextureRect();
}

void Tileset::setTileHeight(int height)
{
	tileSize.y = height;
	updateTextureRect();
}

void Tileset::setTileSize(const Vector2i& size)
{
	tileSize = size;
	updateTextureRect();
}

void Tileset::setImageWidth(int width)
{
	imageSize.x = width;
	updateTextureRect();
}

void Tileset::setImagetHeight(int height)
{
	imageSize.y = height;
	updateTextureRect();
}

void Tileset::setImageSize(const Vector2i & size)
{
	imageSize = size;
	updateTextureRect();
}

void Tileset::setMargin(const Vector2i & margin)
{
	this->margin = margin;
	updateTextureRect();
}

void Tileset::setMargin(int marginX, int marginY)
{
	setMargin({ marginX, marginY });
}

void Tileset::setSpacing(const Vector2i& spacing)
{
	this->spacing = spacing;
	updateTextureRect();
}

void Tileset::setSpacing(int spacingX, int spacingY)
{
	setSpacing({ spacingX, spacingY });
}

void Tileset::setTileNumber(int n)
{
	tileNumber = n;
	updateTextureRect();
}

int Tileset::getTileWidth() const
{
	return tileSize.x;
}

int Tileset::getTileHeight() const
{
	return tileSize.y;
}

const Vector2i& Tileset::getTileSize() const
{
	return tileSize;
}

int Tileset::getImageWidth() const
{
	return imageSize.x;
}

int Tileset::getImageHeight() const
{
	return imageSize.y;
}

const Vector2i& Tileset::getImageSize() const
{
	return imageSize;
}

const Vector2i& Tileset::getMargin() const
{
	return margin;
}

const Vector2i& Tileset::getSpacing() const
{
	return spacing;
}

int Tileset::getTileNumber() const
{
	return tileNumber;
}

IntRect Tileset::tileNumberToRect(int n) const
{
	int tilesPerRow = imageSize.x / (tileSize.x + spacing.x);

	IntRect rect = { 0, 0, tileSize.x, tileSize.y };

	rect.left = margin.x + n % tilesPerRow * (tileSize.x + spacing.x);
	rect.top = margin.y + (int)floor(n / tilesPerRow) * (tileSize.y + spacing.y);

	return rect;
}

IntRect Tileset::currentTileNumberToRect() const
{
	return tileNumberToRect(tileNumber);
}

void Tileset::updateTextureRect()
{
	setTextureRect(currentTileNumberToRect());
}