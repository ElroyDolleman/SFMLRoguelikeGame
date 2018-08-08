#include "weapons\baseweapon.h"

BaseWeapon::BaseWeapon(SpriteAnimation sprite)
	: Entity(sprite)
{
}

int BaseWeapon::GetPower() const
{
	return power;
}

void BaseWeapon::SetOwner(Entity* owner)
{
#if _DEBUG
	if (owner == nullptr)
	{
		printf("Warning: Weapon is getting a nullptr owner.\n");
		return;
	}
#endif
	this->owner = owner;
	hasOnwer = true;

	SetPosition(GetOwner()->GetPosition());
}

bool BaseWeapon::HasOwner() const
{
	return hasOnwer;
}

Entity* BaseWeapon::GetOwner() const
{
	return owner;
}

void BaseWeapon::SetOffset(const Vector2f& offset)
{
	this->offset = offset;
}

void BaseWeapon::SetOffset(float offsetX, float offsetY)
{
	SetOffset({ offsetX, offsetY });
}

void BaseWeapon::Update(float deltaTime)
{
	if (hasOnwer)
		SetPosition(owner->GetPosition() + offset);
}
