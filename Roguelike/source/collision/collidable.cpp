#include "stdafx.h"
#include "collision\collidable.h"

#include "collision\collisionmanager.h"
#include "graphics\spriteanimation.h"

CollidableEntity::CollidableEntity(SpriteAnimation sprite)
	: Entity(sprite)
{
	
}

void CollidableEntity::Move(float x, float y)
{
	MoveX(x);
	MoveY(y);
}

void CollidableEntity::Move(Vector2f direction)
{
	Move(direction.x, direction.y);
}

void CollidableEntity::MoveInAngle(float angle, float speed)
{
	MoveX(cos(angle) * speed);
	MoveY(sin(angle) * speed);
}

void CollidableEntity::MoveX(float amount)
{
	if (amount == 0)
		return;
#if _DEBUG
	if (collisionManager == nullptr)
	{
		printf("Warning: CollidableEntity should't be moved when it doesn't have a reference to the CollisionManager.\n");
		return;
	}
#endif
	sprite.move(amount, 0);
	collisionManager->UpdateCollision(this, { amount, 0 });
}

void CollidableEntity::MoveY(float amount)
{
	if (amount == 0)
		return;
#if _DEBUG
	if (collisionManager == nullptr)
	{
		printf("Warning: CollidableEntity should't be moved when it doesn't have a reference to the CollisionManager.\n");
		return;
	}
#endif
	sprite.move(0, amount);
	collisionManager->UpdateCollision(this, { 0, amount });
}