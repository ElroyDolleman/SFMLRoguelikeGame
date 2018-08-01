#pragma once
#include "stdafx.h"
#include "entities\entity.h"

class BaseWeapon : public Entity
{
public:

	virtual void Attack() = 0;
	virtual bool IsAttacking() const = 0;

	virtual int GetPower() const { return power; }

	//virtual bool Intersects() const override;

protected:

	int power;
};