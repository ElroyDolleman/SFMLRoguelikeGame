#pragma once
#include "map\tile.h"

class Room
{
public:

	Room(Tileset spritesheet, int roomWidth, int roomHeight);
	Room(Tileset spritesheet, Vector2i size);
	~Room();

	void CreateBackgroundTiles(const vector<int>& tileNumbers, const json& tilesetData);

	void Draw(RenderWindow& window);

private:

	Tileset tileset;

	vector<vector<Tile*>> tiles;

	Vector2i size;
};