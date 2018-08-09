#pragma once
#include "entities\entity.h"
#include "interfaces\damagedealer.h"

class BaseWeapon : public Entity, public IDamageDealer
{
public:

	BaseWeapon(SpriteAnimation sprite);

	virtual int GetPower() const;

	void SetOwner(Entity* owner);

	bool HasOwner() const;
	Entity* GetOwner() const;

	virtual float GetStartUpSpeed() const;
	virtual float GetAttackDuration() const;

	virtual void SetOffset(const Vector2f& offset);
	virtual void SetOffset(float offsetX, float offsetY);

	virtual void Update(float deltaTime) override;
	virtual void Draw(RenderWindow& window) override;

protected:

	int power;

	float startUpSpeed;
	float attackDuration;
	float coolDown;

	Vector2f offset = { 0, 0 };

	bool visible = true;

private:

	Entity* owner;
	bool hasOnwer;

	float timer;
};