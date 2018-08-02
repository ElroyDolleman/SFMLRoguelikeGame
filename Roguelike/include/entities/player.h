#pragma once
#include "stdafx.h"
#include "interfaces\damageable.h"
#include "weapons\sword.h"

class Player : public Entity, public IDamageable
{
public:

	static bool PlayWithController;

	Player(SpriteAnimation sprite);
	~Player();

	void Damage(int damage) override;

	const BaseWeapon* GetWeapon() const;

	virtual bool Intersects() const override;
	virtual bool IntersectsHurtbox() const override;

	virtual void Update(float deltaTime) override;

	virtual void UpdateJoystickInput(float deltaTime);
	virtual void UpdateKeyboardInput(float deltaTime);

	virtual void Draw(RenderWindow& window) override;

protected:

	bool inputEnabled = true;

	int health;
	int movementSpeed = 128;
	BaseWeapon* currentWeapon;

	const float diagonalSpeedMultiplier = 0.7071f;
};