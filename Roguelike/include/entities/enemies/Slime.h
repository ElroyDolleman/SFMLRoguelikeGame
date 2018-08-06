#pragma once
#include "entities\enemy.h"
#include "collision\collidable.h"

class Slime : public Enemy, public ICollidable, public IDamageable
{
public:

	Slime(SpriteAnimation sprite);

	// ICollidable override functions
	virtual AABB GetAABBCollider() const override;
	virtual void SetCollidablePositionX(float xPos) override;
	virtual void SetCollidablePositionY(float yPos) override;

	// IDamageable override functions
	virtual bool IntersectsHurtbox() const override;
	virtual AABB GetAABBHurtbox() const;
	virtual void Damage(int damage) override;

	// Entity override functions
	virtual void Update(float deltaTime) override;
	virtual void Move(float x, float y) override;
	virtual void MoveTowards(Vector2f destination, float speed) override;

	// Enemy override functions
	virtual void SetTarget(IDamageable* target) override;
	virtual void LoseTarget() override;

protected:

	const int LeftAnimation = 0;
	const int RightAnimation = 1;

	float speed = 8;
	AABB localHitbox;

	bool hasTarget = false;
	IDamageable* target;
};