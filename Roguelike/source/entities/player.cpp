#include "stdafx.h"
#include "entities/player.h"

#include "weapons/sword.h"
#include "constants.h"

bool Player::PlayWithController = true;

Player::Player(SpriteAnimation sprite)
	: Entity(sprite)
{
	this->sprite.addAnimation(PlayerAnimations::Idle, 200.0f, 0, 0);
	this->sprite.addAnimation(PlayerAnimations::WalkUp, 200.0f, 2, 3);
	this->sprite.addAnimation(PlayerAnimations::WalkDown, 200.0f, 0, 1);
	this->sprite.addAnimation(PlayerAnimations::WalkLeft, 200.0f, 4, 5);
	this->sprite.addAnimation(PlayerAnimations::WalkRight, 200.0f, 6, 7);

	if (PlayWithController && !Joystick::isConnected(0))
	{
		PlayWithController = false;
#if _DEBUG
		printf("Warning: Joystick is not connected or recognized.");
#endif
	}

	localHitbox = { 0, 0, 16, 16 };
}

Player::~Player()
{
	if (currentWeapon != nullptr)
		delete currentWeapon;
}

void Player::Damage(int damage)
{
	health -= damage;
}

const BaseWeapon* Player::GetWeapon() const
{
	return currentWeapon;
}

AABB Player::GetAABBCollider() const
{
	AABB globalHitbox = localHitbox;
	const Vector2f& pos = GetPosition();

	globalHitbox.left = (int)pos.x + localHitbox.left;
	globalHitbox.top = (int)pos.y + localHitbox.top;

	return globalHitbox;
}

void Player::SetCollidablePositionX(float xPos)
{
	SetXPosition(xPos);
}

void Player::SetCollidablePositionY(float yPos)
{
	SetYPosition(yPos);
}

bool Player::IntersectsHurtbox() const
{
	return false;
}

void Player::Update(float deltaTime)
{
	// Update the input if it is enabled
	if (inputEnabled)
	{
		if (PlayWithController)
			UpdateJoystickInput(deltaTime);
		else
			UpdateKeyboardInput(deltaTime);
	}

	// Update the sprite animation
	sprite.update(deltaTime);
}

void Player::UpdateJoystickInput(float deltaTime)
{
	if (!Joystick::isConnected(0))
	{
#if _DEBUG
		printf("Warning: Joystick is disconnected.");
#endif
		PlayWithController = false;
		return;
	}

	if (Joystick::hasAxis(0, Joystick::X) && Joystick::hasAxis(0, Joystick::Y))
	{
		float x = Joystick::getAxisPosition(0, Joystick::X) / 100;
		float y = Joystick::getAxisPosition(0, Joystick::Y) / 100;

		if (x < controls::JoystickDeadZone && x > -controls::JoystickDeadZone) x = 0;
		if (y < controls::JoystickDeadZone && y > -controls::JoystickDeadZone) y = 0;

		// Move the player if the stick has moved
		if (abs(x) > 0 || abs(y) > 0)
		{
			Move(movementSpeed * x * deltaTime, movementSpeed * y * deltaTime);

			// Prevent checking inputs from the dpad if the player is already moving with the stick
			return;
		}
	}

	if (Joystick::hasAxis(0, Joystick::PovX) && Joystick::hasAxis(0, Joystick::PovY))
	{
		float x = roundf(Joystick::getAxisPosition(0, Joystick::PovX) / 100);
		float y = -roundf(Joystick::getAxisPosition(0, Joystick::PovY) / 100);

		GetDirectionBasedOnInput(
			x, y,
			y < 0,
			y > 0,
			x < 0,
			x > 0
		);

		Move(movementSpeed * x * deltaTime, movementSpeed * y * deltaTime);
	}
}

void Player::UpdateKeyboardInput(float deltaTime)
{
	float x = 0.f;
	float y = 0.f;

	GetDirectionBasedOnInput(
		x, y,
		Keyboard::isKeyPressed(controls::UpButton),
		Keyboard::isKeyPressed(controls::DownButton),
		Keyboard::isKeyPressed(controls::LeftButton),
		Keyboard::isKeyPressed(controls::RightButton)
	);

	Move(movementSpeed * x * deltaTime, movementSpeed * y * deltaTime);
}

void Player::GetDirectionBasedOnInput(float& xDirection, float& yDirection, bool up, bool down, bool left, bool right) const
{
	if (up && left)
		xDirection = yDirection = -diagonalSpeedMultiplier;
	else if (down && right)
		xDirection = yDirection = diagonalSpeedMultiplier;
	else if (down && left)
	{
		xDirection = -diagonalSpeedMultiplier;
		yDirection = diagonalSpeedMultiplier;
	}
	else if (up && right)
	{
		xDirection = diagonalSpeedMultiplier;
		yDirection = -diagonalSpeedMultiplier;
	}
	else if (right)
		xDirection = 1.f;
	else if (left)
		xDirection = -1.f;
	else if (up)
		yDirection = -1.f;
	else if (down)
		yDirection = 1.f;
}

void Player::Move(float x, float y)
{
	if (x == 0 && y == 0)
	{
		sprite.switchToAnimation(PlayerAnimations::Idle);
		return;
	}
	else if (abs(x) > abs(y))
	{
		if (x > 0)
			sprite.switchToAnimation(PlayerAnimations::WalkRight);
		else
			sprite.switchToAnimation(PlayerAnimations::WalkLeft);
	}
	else
	{
		if (y > 0)
			sprite.switchToAnimation(PlayerAnimations::WalkDown);
		else
			sprite.switchToAnimation(PlayerAnimations::WalkUp);
	}

	Entity::Move(x, 0);
	ICollidable::UpdateXCollision(x);
	Entity::Move(0, y);
	ICollidable::UpdateYCollision(y);
}

void Player::Draw(RenderWindow& window)
{
	Entity::Draw(window);
}
