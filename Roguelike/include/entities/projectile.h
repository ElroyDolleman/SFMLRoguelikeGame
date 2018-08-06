#pragma once
#include "stdafx.h"
#include "entity.h"

class Projectile : public Entity
{
public:

	//virtual bool Intersects() const override;

	virtual void Update(float deltaTime) override;
};