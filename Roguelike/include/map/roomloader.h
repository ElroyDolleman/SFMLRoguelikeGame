#pragma once
#include "map\room.h"

class RoomLoader
{
public:

	const string roomsFolder = "content\\rooms\\";

	RoomLoader();

	Room* CreateRoom(Texture& texture, const json& roomData, const json& tilesetData);
};