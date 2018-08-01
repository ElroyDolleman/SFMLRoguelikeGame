#pragma once
#include "stdafx.h"
#include "entity.h"
#include "interfaces\damageable.h"

class Enemy : public Entity, public IDamageable
{
public:

	void Damage(int damage) override;

	virtual bool Intersects() const override;

	virtual void Update(float deltaTime) override;

private:

	int health;
};