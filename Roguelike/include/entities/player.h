#pragma once
#include "fwd.h"
#include "collision\collidable.h"
#include "interfaces\damageable.h"

class Player : public CollidableEntity, public IDamageable
{
public:

	enum PlayerAnimations
	{
		Idle,
		WalkLeft,
		WalkRight,
		WalkUp,
		WalkDown,
		Attack,
	};

	static bool PlayWithController;

	Player(SpriteAnimation sprite);
	~Player();

	void Damage(int damage) override;

	const BaseWeapon* GetWeapon() const;

	virtual bool Intersects() const override;
	virtual AABB GetHitbox() const override;
	virtual bool IntersectsHurtbox() const override;

	virtual void Update(float deltaTime) override;

	virtual void UpdateJoystickInput(float deltaTime);
	virtual void UpdateKeyboardInput(float deltaTime);

	void GetDirectionBasedOnInput(float& xDirection, float& yDirection, bool up, bool down, bool left, bool right) const;

	virtual void Move(float x, float y) override;

	virtual void Draw(RenderWindow& window) override;

protected:

	bool inputEnabled = true;

	int health;
	int movementSpeed = 128;
	BaseWeapon* currentWeapon;

	const float diagonalSpeedMultiplier = 0.7071f;

	AABB localHitbox;
};