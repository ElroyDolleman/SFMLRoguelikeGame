#pragma once
#include "fwd.h"

class CollisionManager
{
public:

	CollisionManager();
	CollisionManager(Room* firstRoom);

	void ChangeRoom(Room* newRoom);

	void AddCollidableEntity(ICollidable* entity);

	void UpdateCollision(ICollidable* entity, const Vector2f moved);

private:

	void SolveCollisionHorizontal(ICollidable* entity, const AABB& collider);
	void SolveCollisionVertical(ICollidable* entity, const AABB& collider);

	map<int, ICollidable*> entities;
	Room* currentRoom;
};