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
	spacing = sheetData["spacing"].get<int>();
	margin = sheetData["margin"].get<int>();
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

void Tileset::setMargin(int margin)
{
	this->margin = margin;
	updateTextureRect();
}

void Tileset::setSpacing(int spacing)
{
	this->spacing = spacing;
	updateTextureRect();
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

int Tileset::getMargin() const
{
	return margin;
}

int Tileset::getSpacing() const
{
	return spacing;
}

int Tileset::getTileNumber() const
{
	return tileNumber;
}

void Tileset::updateTextureRect()
{
	int tilesPerRow = imageSize.x / (tileSize.x + spacing);

	IntRect newTextureRect = { 0, 0, tileSize.x, tileSize.y };

	newTextureRect.left = margin + tileNumber % tilesPerRow * (tileSize.x + spacing);
	newTextureRect.top = margin + (int)floor(tileNumber / tilesPerRow) * (tileSize.y + spacing);

	setTextureRect(newTextureRect);
}