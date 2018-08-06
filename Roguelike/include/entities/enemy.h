#pragma once
#include "entity.h"
#include "interfaces\damageable.h"

class Enemy : public Entity
{
public:

	Enemy(SpriteAnimation sprite)
		: Entity(sprite)
	{}

	virtual void SetTarget(IDamageable* target) {}
	virtual void LoseTarget() {}

protected:

	int health;
};