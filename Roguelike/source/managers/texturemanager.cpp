#include "stdafx.h"
#include "managers\texturemanager.h"

TextureManager::TextureManager()
{
	spritesheets.insert(SpriteSheetNames::Map, LoadTexture("spritesheet"));
	spritesheets.insert(SpriteSheetNames::Player, LoadTexture("playersheet"));
	spritesheets.insert(SpriteSheetNames::Enemies, LoadTexture("enemysheet"));
}

Texture& TextureManager::GetSpriteSheet(SpriteSheetNames name)
{
	return spritesheets[name];
}

Texture TextureManager::LoadTexture(string path)
{
	Texture texture;
	path = contentFolder + path;

#if _DEBUG
	if (!texture.loadFromFile(path))
		printf("Warning: Failed to load texture path");
#else
	texture.loadFromFile(path);
#endif
	
	return texture;
}
