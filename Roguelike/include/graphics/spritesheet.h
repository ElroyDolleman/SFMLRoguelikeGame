#pragma once
#include "stdafx.h"

class SpriteSheet : public Sprite
{
public:

	SpriteSheet();
	SpriteSheet(const Texture& texture, int sheetWidth, int sheetHeight, int tileWidth, int tileHeight);
	SpriteSheet(const Texture& texture, const Vector2i& sheetSize, const Vector2i& tileSize);

	void setTileWidth(int width);
	void setTileHeight(int height);
	void setTileSize(const Vector2i& size);

	void setSheetWidth(int width);
	void setSheetHeight(int height);
	void setSheetSize(const Vector2i& size);

	void setOffset(int offsetX, int offsetY);
	void setOffset(const Vector2i& offset);

	void setInterspace(int interspaceWidth, int interspaceHeight);
	void setInterspace(const Vector2i& interspace);

	void setTileNumber(int n);

	int getTileWidth() const;
	int getTileHeight() const;
	const Vector2i& getTileSize() const;

	int getSheetWidth() const;
	int getSheetHeight() const;
	const Vector2i& getSheetSize() const;

	const Vector2i& getOffset() const;
	const Vector2i& getInterspace() const;

	int getTileNumber() const;

protected:

	int tileNumber = 0;
	Vector2i tileSize = { 0, 0 };
	Vector2i sheetSize = { 0, 0 };
	Vector2i interspace = { 0, 0 };
	Vector2i offset = { 0, 0 };

	void updateTextureRect();
};