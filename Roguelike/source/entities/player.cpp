#include "stdafx.h"
#include "entities/player.h"

void Player::Damage(int damage)
{
}

const BaseWeapon* Player::GetWeapon() const
{
	return currentWeapon;
}

bool Player::Intersects() const
{
	return false;
}

bool Player::IntersectsHurtbox() const
{
	return false;
}

void Player::Update(float deltaTime)
{
}