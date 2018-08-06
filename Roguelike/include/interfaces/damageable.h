#pragma once
#include "collision\aabb.h"

class IDamageable
{
public:

	virtual void Damage(int damage) = 0;

	virtual bool IntersectsHurtbox() const = 0;

	virtual AABB GetAABBHurtbox() const = 0;
};