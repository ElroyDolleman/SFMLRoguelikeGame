#include "stdafx.h"
#include "constants.h"
#include "map\room.h"

Room::Room(Tileset tileset, int roomWidth, int roomHeight)
	: tileset(tileset)
{
	size = { roomWidth, roomHeight };
}

Room::Room(Tileset tileset, Vector2i size)
	: Room(tileset, size.x, size.y)
{
}

Room::~Room()
{
}

void Room::CreateBackgroundTiles(const vector<int>& tileNumbers, const json& tilesetData)
{
	for (int i = 0; i < tileNumbers.size(); i++)
	{
		int x = i % size.x;
		int y = (int)floor(i / size.x);

		if (i % size.x == 0)
			tiles.push_back({});

		Tileset tileSprite = tileset;
		tileSprite.setTileNumber(tileNumbers[i] - 1);
		tiles[y].push_back(new Tile({ x*grid::size, y*grid::size, grid::size, grid::size }, tileSprite, tilesetData));
	}
}

void Room::Draw(RenderWindow& window)
{
	// Draw every tile
	for (vector<Tile*>& rows : tiles)
		for (Tile* tile : rows)
			tile->Draw(window);
}
