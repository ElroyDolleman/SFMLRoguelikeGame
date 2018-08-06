#pragma once
#include "fwd.h"
#include "entities\entity.h"
#include "collision\collidable.h"
#include "interfaces\damageable.h"

class Player : public Entity, public ICollidable, public IDamageable
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

	const BaseWeapon* GetWeapon() const;

	// ICollidable override functions
	virtual AABB GetAABBCollider() const override;
	virtual void SetCollidablePositionX(float yPos) override;
	virtual void SetCollidablePositionY(float yPos) override;

	// IDamageable override functions
	virtual bool IntersectsHurtbox() const override;
	virtual void Damage(int damage) override;

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