#include "stdafx.h"
#include "weapons/sword.h"

Sword::Sword(SpriteAnimation sprite)
	: BaseWeapon(sprite)
{
	this->sprite.setOrigin(8, 2);
}

void Sword::StartAttack()
{
	IDamageDealer::StartAttack();

	//visible = true;
}

void Sword::StopAttack()
{
	IDamageDealer::StopAttack();

	//visible = false;
}

void Sword::Update(float deltaTime)
{
	BaseWeapon::Update(deltaTime);


}