#include "stdafx.h"
#include "collision\collisionmanager.h"

#include "collision\collidable.h"
#include "map\room.h"
#include "map\tile.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::CollisionManager(Room* firstRoom)
	: currentRoom(firstRoom)
{
}

void CollisionManager::ChangeRoom(Room* newRoom)
{
	currentRoom = newRoom;
}

void CollisionManager::AddCollidableEntity(CollidableEntity* entity)
{
	entity->collisionManager = this;

	int size = (int)entities.size();
	entities[size] = entity;
	entity->collidableID = size;
}

void CollisionManager::UpdateCollision(CollidableEntity* entity, const Vector2f moved)
{
#if _DEBUG
	if (moved.x == 0 && moved.y == 0)
	{
		printf("Warning: Attempting to do a collision check for an entity that hasn't moved.\n");
		return;
	}
	if (currentRoom == nullptr)
	{
		printf("Warning: Attempting to do a collision check but the current room is a nullptr.\n");
		return;
	}
#endif

	const AABB& entityBox = entity->GetHitbox();

	// Get the top left tile that the entity is overlapping
	Vector2i gridLocTop = currentRoom->ToGridLocation(entityBox.left, entityBox.top);

	// Get the bottom right tile that the entity is overlapping
	Vector2i gridLocBottom = currentRoom->ToGridLocation(entityBox.getRight(), entityBox.getBottom());

	// Iterate from the top left tile to the bottom right
	for (int x = gridLocTop.x; x <= gridLocBottom.x; x++)
	{
		for (int y = gridLocTop.y; y <= gridLocBottom.y; y++)
		{
			Tile* tile = currentRoom->GetTile(x, y);

			// Continue the for loop if there is no tile or the tile is not solid
			if (tile == nullptr || !tile->IsSolid())
				continue;

			const AABB& tileBox = tile->GetHitbox();
			if (tileBox.intersects(entityBox))
			{
				if (moved.x != 0)
					SolveCollisionHorizontal(entity, tileBox);
				if (moved.y != 0)
					SolveCollisionVertical(entity, tileBox);
			}
		}
	}

}

void CollisionManager::SolveCollisionHorizontal(CollidableEntity* entity, const AABB& collider)
{
	const AABB& entityBox = entity->GetHitbox();
	int depth = collider.getXDepth(entityBox);

	if (collider.isOnLeftOf(entityBox))
		entity->SetXPosition((float)entityBox.left + depth);
	else
		entity->SetXPosition((float)entityBox.left - depth);
}

void CollisionManager::SolveCollisionVertical(CollidableEntity* entity, const AABB& collider)
{
	const AABB& entityBox = entity->GetHitbox();
	int depth = collider.getYDepth(entityBox);

	if (collider.isAbove(entityBox))
		entity->SetYPosition((float)entityBox.top + depth);
	else
		entity->SetYPosition((float)entityBox.top - depth);
}
