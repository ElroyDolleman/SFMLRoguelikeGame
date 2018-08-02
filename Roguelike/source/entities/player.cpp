#include "stdafx.h"
#include "entities/player.h"

bool Player::PlayWithController = true;

Player::Player(Sprite sprite)
	: Entity(sprite)
{
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
}

void Player::UpdateJoystickInput(float deltaTime)
{
	if (Joystick::isConnected(0) && Joystick::hasAxis(0, Joystick::X) && Joystick::hasAxis(0, Joystick::Y))
	{
		float x = Joystick::getAxisPosition(0, Joystick::X) / 100;
		float y = Joystick::getAxisPosition(0, Joystick::Y) / 100;

		if (x < 0.2f && x > -0.2f) x = 0;
		if (y < 0.2f && y > -0.2f) y = 0;

		Move(movementSpeed * x * deltaTime, movementSpeed * y * deltaTime);
	}
}

void Player::UpdateKeyboardInput(float deltaTime)
{
	float x = 0.f;
	float y = 0.f;

	bool top = Keyboard::isKeyPressed(Keyboard::W);
	bool right = Keyboard::isKeyPressed(Keyboard::D);
	bool down = Keyboard::isKeyPressed(Keyboard::S);
	bool left = Keyboard::isKeyPressed(Keyboard::A);

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
