#pragma once
#include "weapons\baseweapon.h"

class Sword : public BaseWeapon
{
public:

	Sword(SpriteAnimation sprite);

	virtual void Attack() override;
	virtual bool IsAttacking() const override;

	virtual void Update(float deltaTime) override;

protected:


};