#include "stdafx.h"
#include "managers\contentloader.h"

ContentLoader::ContentLoader()
{
}

ContentLoader::~ContentLoader()
{
}

json ContentLoader::LoadJSON(string path)
{
	json j;
	ifstream file(ContentPath + path + ".json");
	file >> j;
	return j;
}

Texture& ContentLoader::LoadTexture(string path)
{
#if _DEBUG
	auto it = loadedTextures.find(path);
	if (it != loadedTextures.end())
	{
		printf("Warning: Texture %s was already loaded previously. Prevent loading the same texture twice.\n", path.c_str());
		return it->second;
	}

	loadedTextures[path] = Texture();

	if (!loadedTextures[path].loadFromFile(ContentPath + path))
		printf("Warning: Failed to load texture %s\n", path.c_str());
#else
	loadedTextures[path] = Texture();
	loadedTextures[path].loadFromFile(path);
#endif

	return loadedTextures[path];
}
