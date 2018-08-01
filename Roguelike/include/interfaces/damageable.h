#pragma once
#include "stdafx.h"

class IDamageable
{
public:

	virtual void Damage(int damage) = 0;

	virtual bool IntersectsHurtbox() const = 0;
};