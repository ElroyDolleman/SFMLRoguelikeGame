#pragma once

class TextureManager
{
public:

	enum class SpriteSheetNames
	{
		Map,
		Player,
		Enemies,
	};

	TextureManager();

	Texture& GetSpriteSheet(SpriteSheetNames name);

private:

	Texture LoadTexture(string path);

	map<SpriteSheetNames, Texture> spritesheets;

	const string contentFolder = "content\\";
};