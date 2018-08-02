#pragma once
#include "map\tile.h"

class Room
{
public:

	Room();
	~Room();

	void Draw(RenderWindow& window);

private:

	vector<vector<Tile*>> tiles;
};