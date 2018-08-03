#pragma once

class ContentLoader
{
public:

	const string ContentPath = "content\\";

	ContentLoader();
	~ContentLoader();

	// Loads a json file. No .json extension needed.
	json LoadJSON(string path);

	// Loads a texture. Extension should be filled in manually, such as .png
	Texture& LoadTexture(string path);

private:

	// Store all loaded textures
	map<string, Texture> loadedTextures;
};