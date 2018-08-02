#include "entities/player.h"
#include "stdafx.h"
#include "constants.h"

bool Player::PlayWithController = false;

Player::Player(SpriteAnimation sprite)
	: Entity(sprite)
{
	this->sprite.addAnimation(PlayerAnimations::Idle, 200.0f, 0, 0);
	this->sprite.addAnimation(PlayerAnimations::WalkUp, 200.0f, 2, 3);
	this->sprite.addAnimation(PlayerAnimations::WalkDown, 200.0f, 0, 1);
	this->sprite.addAnimation(PlayerAnimations::WalkLeft, 200.0f, 4, 5);
	this->sprite.addAnimation(PlayerAnimations::WalkRight, 200.0f, 6, 7);
}

Player::~Player()
{
	if (currentWeapon != nullptr)
		delete currentWeapon;
}

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
	if (Joystick::isConnected(0) && Joystick::hasAxis(0, Joystick::X) && Joystick::hasAxis(0, Joystick::Y))
	{
		float x = Joystick::getAxisPosition(0, Joystick::X) / 100;
		float y = Joystick::getAxisPosition(0, Joystick::Y) / 100;

		if (x < controls::JoystickDeadZone && x > -controls::JoystickDeadZone) x = 0;
		if (y < controls::JoystickDeadZone && y > -controls::JoystickDeadZone) y = 0;

		Move(movementSpeed * x * deltaTime, movementSpeed * y * deltaTime);
	}
}

void Player::UpdateKeyboardInput(float deltaTime)
{
	float x = 0.f;
	float y = 0.f;

	bool top = Keyboard::isKeyPressed(controls::UpButton);
	bool right = Keyboard::isKeyPressed(controls::RightButton);
	bool down = Keyboard::isKeyPressed(controls::DownButton);
	bool left = Keyboard::isKeyPressed(controls::LeftButton);

	if (top && left)
		x = y = -diagonalSpeedMultiplier;
	else if (down && right)
		x = y = diagonalSpeedMultiplier;
	else if (down && left)
	{
		x = -diagonalSpeedMultiplier;
		y = diagonalSpeedMultiplier;
	}
	else if (top && right)
	{
		x = diagonalSpeedMultiplier;
		y = -diagonalSpeedMultiplier;
	}
	else if (right)
		x = 1.f;
	else if (left)
		x = -1.f;
	else if (top)
		y = -1.f;
	else if (down)
		y = 1.f;

	Move(movementSpeed * x * deltaTime, movementSpeed * y * deltaTime);
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

	Entity::Move(x, y);
}

void Player::Draw(RenderWindow& window)
{
	Entity::Draw(window);
}
