#include "stdafx.h"
#include "map\room.h"

#include "constants.h"
#include "map\tile.h"
#include "entities\entity.h"

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

void Room::CreateTiles(const vector<int>& tileNumbers, const json& tilesetData)
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

Tile* Room::GetTile(int x, int y) const
{
	if (x < 0 || x >= size.x || y < 0 || y >= size.y)
		return nullptr;

	return tiles[y][x];
}

Vector2i Room::ToGridLocation(int x, int y) const
{
	return Vector2i((int)floor(x / grid::size), (int)floor(y / grid::size));
}

Vector2i Room::ToGridLocation(float x, float y) const
{
	return Vector2i((int)floor(x / grid::size), (int)floor(y / grid::size));
}

Vector2i Room::ToGridLocation(Vector2f worldPosition) const
{
	return ToGridLocation(worldPosition.x, worldPosition.y);
}

Vector2f Room::ToWorldPosition(int x, int y) const
{
	return Vector2f();
}

Vector2f Room::ToWorldPosition(const Vector2i& gridLocation) const
{
	return Vector2f();
}

void Room::Draw(RenderWindow& window)
{
	// Draw every tile
	for (vector<Tile*>& rows : tiles)
		for (Tile* tile : rows)
			tile->Draw(window);
}
