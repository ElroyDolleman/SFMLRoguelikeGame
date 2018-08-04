#pragma once
#include "fwd.h"

class CollisionManager
{
public:

	CollisionManager();
	CollisionManager(Room* firstRoom);

	void ChangeRoom(Room* newRoom);

	void AddCollidableEntity(CollidableEntity* entity);

	void UpdateCollision(CollidableEntity* entity, const Vector2f moved);

private:

	void SolveCollisionHorizontal(CollidableEntity* entity, const AABB& collider);
	void SolveCollisionVertical(CollidableEntity* entity, const AABB& collider);

	map<int, CollidableEntity*> entities;
	Room* currentRoom;
};