#pragma once
#include "stdafx.h"
#include "interfaces\damageable.h"
#include "weapons\sword.h"

class Player : public Entity, public IDamageable
{
public:

	static bool PlayWithController;

	Player(Sprite sprite);
	~Player();

	void Damage(int damage) override;

	const BaseWeapon* GetWeapon() const;

	virtual bool Intersects() const override;
	virtual bool IntersectsHurtbox() const override;

	virtual void Update(float deltaTime) override;

	virtual void UpdateJoystickInput(float deltaTime);
	virtual void UpdateKeyboardInput(float deltaTime);

protected:

	bool inputEnabled = true;

	int health;
	int movementSpeed = 4;
	BaseWeapon* currentWeapon;

	const float diagonalSpeedMultiplier = 0.7071f;
};

bool Player::PlayWithController = true;