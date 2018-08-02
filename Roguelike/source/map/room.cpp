#include "stdafx.h"
#include "map\room.h"

Room::Room()
{
}

Room::~Room()
{
}

void Room::Draw(RenderWindow& window)
{
	// Draw every tile
	for (vector<Tile*>& rows : tiles)
		for (Tile* tile : rows)
			tile->Draw(window);
}
