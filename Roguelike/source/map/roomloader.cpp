#include "stdafx.h"
#include "constants.h"
#include "map\roomloader.h"

RoomLoader::RoomLoader()
{
}

Room* RoomLoader::CreateRoom(Texture& texture, const json& roomData, const json& tilesetData)
{
	vector<int> tileNumbers0 = roomData["layers"][0]["data"].get<vector<int>>();

	Room* room = new Room(Tileset(texture, tilesetData), roomData["width"], roomData["height"]);
	room->CreateTiles(tileNumbers0, tilesetData);

	return room;
}
