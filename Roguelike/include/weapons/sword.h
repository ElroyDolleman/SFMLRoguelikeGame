#pragma once
#include "weapons\baseweapon.h"

class Sword : public BaseWeapon
{
public:

	Sword(SpriteAnimation sprite);

	virtual void StartAttack() override;
	virtual void StopAttack() override;

	virtual void Update(float deltaTime) override;

private:

	float timer;
};