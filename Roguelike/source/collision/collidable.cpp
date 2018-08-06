#include "stdafx.h"
#include "collision\collidable.h"

#include "collision\collisionmanager.h"

ICollidable::ICollidable()
{
}

void ICollidable::UpdateXCollision(float movedAmout)
{
	// No need for collision checks if there was no movement
	if (movedAmout == 0) return;

	// Checks if this collidable is 
#if _DEBUG
	if (collisionManager == nullptr)
	{
		printf("Warning: CollidableEntity should't be moved when it doesn't have a reference to the CollisionManager.\n");
		return;
	}
#endif

	// Update the collision checks in the collision manager
	collisionManager->UpdateCollision(this, { movedAmout, 0 });
}

void ICollidable::UpdateYCollision(float movedAmout)
{
	// No need for collision checks if there was no movement
	if (movedAmout == 0) return;

	// Checks if this collidable is 
#if _DEBUG
	if (collisionManager == nullptr)
	{
		printf("Warning: CollidableEntity should't be moved when it doesn't have a reference to the CollisionManager.\n");
		return;
	}
#endif

	// Update the collision checks in the collision manager
	collisionManager->UpdateCollision(this, { 0, movedAmout });
}