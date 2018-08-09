#pragma once
#include "collision\aabb.h"

class IDamageable
{
public:

	virtual void Damage(int damage) = 0;

	virtual bool IntersectsHurtbox(const AABB& damageBox) const {
		return IntersectsHurtbox({ damageBox });
	}
	virtual bool IntersectsHurtbox(const vector<AABB>& damageBoxes) const = 0;
};