#pragma once

class IDamageable
{
public:

	virtual void Damage(int damage) = 0;

	virtual bool IntersectsHurtbox() const = 0;
};