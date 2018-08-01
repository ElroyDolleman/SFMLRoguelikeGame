#pragma once
#include "stdafx.h"
#include "interfaces\damageable.h"
#include "weapons\sword.h"

class Player : public Entity, public IDamageable
{
public:

	void Damage(int damage) override;

	const BaseWeapon* GetWeapon() const;

	virtual bool Intersects() const override;
	virtual bool IntersectsHurtbox() const override;

	virtual void Update(float deltaTime) override;

protected:

	int health;
	BaseWeapon* currentWeapon;
};