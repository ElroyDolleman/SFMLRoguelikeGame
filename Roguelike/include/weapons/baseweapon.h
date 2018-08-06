#pragma once
#include "entities\entity.h"

class BaseWeapon : public Entity
{
public:

	BaseWeapon(SpriteAnimation sprite);

	virtual void Attack() = 0;
	virtual bool IsAttacking() const = 0;

	virtual int GetPower() const;

	void SetOwner(Entity* owner);

	bool HasOwner() const;
	Entity* GetOwner() const;

	void SetOffset(const Vector2f& offset);
	void SetOffset(float offsetX, float offsetY);

	virtual void Update(float deltaTime) override;

protected:

	int power;
	Vector2f offset = { 0, 0 };

private:

	Entity* owner;
	bool hasOnwer;
};