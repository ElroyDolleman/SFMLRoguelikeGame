#pragma once
#include "fwd.h"
#include "collision\aabb.h"

class ICollidable
{
	friend class CollisionManager;

public:

	ICollidable();

	// Updates the collision checks on the x axis. Always call this function after moving on the x axis to make sure that the collision is working.
	void UpdateXCollision(float movedAmout);
	// Updates the collision checks on the y axis. Always call this function after moving on the y axis to make sure that the collision is working.
	void UpdateYCollision(float movedAmout);

	virtual AABB GetAABBCollider() const = 0;

	// Set the x position of the collidable. This is used to adjust the position if it collides with collision.
	virtual void SetCollidablePositionX(float xPos) = 0;
	// Set the y position of the collidable. This is used to adjust the position if it collides with collision.
	virtual void SetCollidablePositionY(float yPos) = 0;

private:

	int collidableID;
	CollisionManager* collisionManager;
};