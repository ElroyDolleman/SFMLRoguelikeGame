#pragma once
#include "weapons\baseweapon.h"

class Sword : public BaseWeapon
{
public:

	virtual void Attack() override;
	virtual bool IsAttacking() const override;
	virtual bool Intersects() const override;

	virtual void Update(float deltaTime) override;

protected:


};