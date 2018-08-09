#pragma once
#include "fwd.h"
#include "entities\entity.h"
#include "collision\collidable.h"
#include "interfaces\damageable.h"

class Player : public Entity, public ICollidable, public IDamageable
{
protected:
	enum FacingDirections
	{
		Up = 0,
		Down = 1 << 1,
		Left = 1 << 2,
		Right = 1 << 3,
	};

	enum States
	{
		Idle = 1 << 4,
		Walking = 1 << 5,
		Attacking = 1 << 6,
	};

	struct PlayerFrameData
	{
		Vector2f rightHandPosition;
		Vector2f leftHandPosition;
	};

public:

	static bool PlayWithController;

	Player(SpriteAnimation sprite);
	~Player();

	// Initialize functions
	void CreateAnimations();
	void CreateFrameData();

	// Combat Functions
	void ObtainWeapon(BaseWeapon* newWeapon);
	BaseWeapon* GetWeapon();
	bool HasWeapon() const;
	void UpdateWeaponOrientation();

	void StartAttack();
	void StopAttack();

	// ICollidable override functions
	virtual AABB GetAABBCollider() const override;
	virtual void SetCollidablePositionX(float xPos) override;
	virtual void SetCollidablePositionY(float yPos) override;

	// IDamageable override functions
	virtual bool IntersectsHurtbox(const vector<AABB>& damageBoxes) const override;
	virtual void Damage(int damage) override;
	virtual AABB GetAABBHurtbox() const;

	// Entity override functions
	virtual void Update(float deltaTime) override;
	virtual void Move(float x, float y) override;
	virtual void Draw(RenderWindow& window) override;

protected:

	// Input
	bool inputEnabled = true;

	virtual void UpdateJoystickInput(float deltaTime);
	virtual void UpdateKeyboardInput(float deltaTime);

	// Movement
	const float diagonalSpeedMultiplier = 0.7071f;
	int movementSpeed = 80;

	Vector2i GetDirectionVector(FacingDirections direction) const;
	Vector2f GetDirectionVector(bool pressedDown, bool pressedUp, bool pressedLeft, bool pressedRight) const;
	FacingDirections GetDirectionEnum(const Vector2i& direction) const;
	FacingDirections GetDirectionEnum(const Vector2f& direction) const;
	FacingDirections GetDirectionEnum(int directionX, int directionY) const;
	FacingDirections GetDirectionEnum(float directionX, float directionY) const;

	// Combat
	int health;
	bool invulnerable = false;

	bool hasWeapon = false;
	BaseWeapon* currentWeapon;

	AABB localHitbox;

	// State Management
	States currentState = States::Idle;
	FacingDirections currentFacingDirection = FacingDirections::Down;

	virtual void ChangeState(States newState);
	virtual void ChangeDirection(FacingDirections newDirection);
	virtual void UpdateAnimation();

	// Animation
	map<int, PlayerFrameData> frameData;

	int GetFrameID(int animKey, int frameNumber);
	virtual void AddFrameData(int id, Vector2f rightHandPosition, Vector2f leftHandPosition);
};