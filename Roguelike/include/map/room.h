#pragma once
#include "graphics\tileset.h"
#include "fwd.h"

class Room
{
public:

	Room(Tileset spritesheet, int roomWidth, int roomHeight);
	Room(Tileset spritesheet, Vector2i size);
	~Room();

	void CreateTiles(const vector<int>& tileNumbers, const json& tilesetData);

	Tile* GetTile(int x, int y) const;

	Vector2i ToGridLocation(float x, float y) const;
	Vector2i ToGridLocation(Vector2f worldPosition) const;

	Vector2f ToWorldPosition(int x, int y) const;
	Vector2f ToWorldPosition(const Vector2i& gridLocation) const;

	bool CollisionCheck(Entity& entity);

	void Draw(RenderWindow& window);

private:

	Tileset tileset;
	Vector2i size;

	vector<vector<Tile*>> tiles;
};