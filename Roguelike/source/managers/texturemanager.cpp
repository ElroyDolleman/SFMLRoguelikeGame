#include "stdafx.h"
#include "managers\texturemanager.h"

TextureManager::TextureManager()
{
	spritesheets = {
		{ SpriteSheetNames::Map,{ LoadTexture("spritesheet.png") } },
		{ SpriteSheetNames::Player,{ LoadTexture("playersheet.png") } },
		{ SpriteSheetNames::Enemies,{ LoadTexture("enemysheet.png") } }
	};
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
		printf("Warning: Failed to load texture %s\n", path.c_str());
#else
	texture.loadFromFile(path);
#endif
	
	return texture;
}
