#pragma once
#include "fwd.h"
#include "entities\entity.h"
#include "collision\aabb.h"

class CollidableEntity : public Entity
{
	friend class CollisionManager;

public:

	CollidableEntity(SpriteAnimation sprite);

	void Move(float x, float y) override;
	void Move(Vector2f direction) override;

	void MoveInAngle(float angle, float speed) override;
	
	void MoveX(float amount);
	void MoveY(float amount);

	virtual bool Intersects() const = 0;
	virtual AABB GetHitbox() const = 0;

	virtual void Update(float deltaTime) = 0;

private:

	int collidableID;
	CollisionManager* collisionManager;
};