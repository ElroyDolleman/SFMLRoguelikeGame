#pragma once
#include "stdafx.h"

class Tileset : public Sprite
{
public:

	Tileset();
	Tileset(const Texture& texture, int imageWidth, int imageHeight, int tileWidth, int tileHeight);
	Tileset(const Texture& texture, const Vector2i& imageSize, const Vector2i& tileSize);
	Tileset(const Texture& texture, const json& sheetData);

	void setTileWidth(int width);
	void setTileHeight(int height);
	void setTileSize(const Vector2i& size);

	void setImageWidth(int width);
	void setImagetHeight(int height);
	void setImageSize(const Vector2i& size);

	void setMargin(int margin);
	void setSpacing(int spacing);

	void setTileNumber(int n);

	int getTileWidth() const;
	int getTileHeight() const;
	const Vector2i& getTileSize() const;

	int getImageWidth() const;
	int getImageHeight() const;
	const Vector2i& getImageSize() const;

	int getMargin() const;
	int getSpacing() const;

	int getTileNumber() const;

protected:

	int tileNumber = 0;
	Vector2i tileSize = { 0, 0 };
	Vector2i imageSize = { 0, 0 };
	int spacing = 0;
	int margin = 0;

	void updateTextureRect();
};