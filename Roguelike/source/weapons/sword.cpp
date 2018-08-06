#include "stdafx.h"
#include "weapons/sword.h"

Sword::Sword(SpriteAnimation sprite)
	: BaseWeapon(sprite)
{
	this->sprite.setOrigin(2, 8);
}

void Sword::Attack()
{

}

bool Sword::IsAttacking() const
{
	return false;
}

void Sword::Update(float deltaTime)
{
	BaseWeapon::Update(deltaTime);


}