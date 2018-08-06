#pragma once

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

	void setMargin(const Vector2i& margin);
	void setMargin(int marginX, int marginY);

	void setSpacing(const Vector2i& spacing);
	void setSpacing(int spacingX, int spacingY);

	void setTileNumber(int n);

	int getTileWidth() const;
	int getTileHeight() const;
	const Vector2i& getTileSize() const;

	int getImageWidth() const;
	int getImageHeight() const;
	const Vector2i& getImageSize() const;

	const Vector2i& getMargin() const;
	const Vector2i& getSpacing() const;

	int getTileNumber() const;

protected:

	int tileNumber = 0;
	Vector2i tileSize = { 0, 0 };
	Vector2i imageSize = { 0, 0 };
	Vector2i spacing = { 0, 0 };
	Vector2i margin = { 0, 0 };

	void updateTextureRect();
};