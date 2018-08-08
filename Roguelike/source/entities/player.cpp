#include "stdafx.h"
#include "entities/player.h"

#include "weapons/sword.h"
#include "constants.h"

bool Player::PlayWithController = true;

Player::Player(SpriteAnimation sprite)
	: Entity(sprite)
{
	CreateAnimations();

	localHitbox = { 3, 5, 16, 16 };

	// Check if the player will be controlled with a joystick
	if (PlayWithController && !Joystick::isConnected(0))
	{
		PlayWithController = false;
#if _DEBUG
		printf("Warning: Joystick is not connected or recognized.\n");
#endif
	}
}

Player::~Player()
{
	if (currentWeapon != nullptr)
		delete currentWeapon;
}

void Player::Damage(int damage)
{
	if (invulnerable)
		return;

	health -= damage;
}

AABB Player::GetAABBHurtbox() const
{
	return GetAABBCollider();
}

void Player::CreateAnimations()
{
	// TODO: Animation speed needs to be more dynamic and not defined in a magic number
	
	sprite.addAnimation(States::Idle | FacingDirections::Down, 140.f, 0);
	sprite.addAnimation(States::Idle | FacingDirections::Up, 140.f, 3);
	sprite.addAnimation(States::Idle | FacingDirections::Right, 140.f, 6);
	sprite.addAnimation(States::Idle | FacingDirections::Left, 140.f, 9);

	sprite.addAnimation(States::Walking | FacingDirections::Down, 140.f, { 0, 1, 0, 2 });
	sprite.addAnimation(States::Walking | FacingDirections::Up, 140.f, { 3, 4, 3, 5 });
	sprite.addAnimation(States::Walking | FacingDirections::Right, 140.f, 7, 8);
	sprite.addAnimation(States::Walking | FacingDirections::Left, 140.f, 10, 11);

	sprite.addAnimation(States::Attacking | FacingDirections::Down, 140.f, { 12, 13, 12, 0 });
	sprite.addAnimation(States::Attacking | FacingDirections::Up, 140.f, { 15, 16, 15, 3 });
	sprite.addAnimation(States::Attacking | FacingDirections::Right, 140.f, { 18, 19, 18, 6 });
	sprite.addAnimation(States::Attacking | FacingDirections::Left, 140.f, { 21, 22, 21, 9 });

	UpdateAnimation();
}

void Player::ObtainWeapon(BaseWeapon* newWeapon)
{
	// TODO: Think about what will happen with the old weapon

	if (hasWeapon)
		delete currentWeapon;

	currentWeapon = newWeapon;
	hasWeapon = true;

	currentWeapon->SetOwner(this);
	currentWeapon->SetOffset(GetWeaponOffset());
}

const BaseWeapon* Player::GetWeapon() const
{
	return currentWeapon;
}

bool Player::HasWeapon() const
{
#if _DEBUG
	if (hasWeapon && currentWeapon == nullptr)
	{
		printf("Warning: player class attempts to return it has a weapon but it does not.\n");
		return false;
	}
#endif

	return hasWeapon;
}

Vector2f Player::GetWeaponOffset() const
{
	//const Vector2i& dir = GetDirectionBasedOnAnimation();

	//if (dir.y < 0)
	//{
	//	currentWeapon->SetRotation(270);
	//	return { 12, 4 };
	//}
	//if (dir.y > 0)
	//{
	//	currentWeapon->SetRotation(90);
	//	return { 12, 10 };
	//}
	//if (dir.x > 0)
	//{
	//	currentWeapon->SetRotation(0);
	//	return { 10, 12 };
	//}
	//if (dir.x < 0)
	//{
	//	currentWeapon->SetRotation(180);
	//	return { 6, 12 };
	//}

	return Vector2f();
}

void Player::StartAttack()
{
	ChangeState(States::Attacking);

	// TODO: Check extra direction input for quick turnarounds

	sprite.SetLooping(false);
	UpdateAnimation();

	inputEnabled = false;
}

void Player::StopAttack()
{
	ChangeState(States::Idle);
	sprite.SetLooping(true);

	inputEnabled = true;
}

AABB Player::GetAABBCollider() const
{
	AABB globalHitbox = localHitbox;
	const Vector2f& pos = GetPosition();

	globalHitbox.left = static_cast<int>(roundf(pos.x)) + localHitbox.left;
	globalHitbox.top = static_cast<int>(roundf(pos.y)) + localHitbox.top;

	return globalHitbox;
}

void Player::SetCollidablePositionX(float xPos)
{
	SetXPosition(xPos - localHitbox.left);
}

void Player::SetCollidablePositionY(float yPos)
{
	SetYPosition(yPos - localHitbox.top);
}

bool Player::IntersectsHurtbox() const
{
	return false;
}

void Player::Update(float deltaTime)
{
	if (currentState == States::Attacking)
	{
		// TODO: Check weapon if attack startup is over
		if (sprite.hasFinishedPlaying())
			StopAttack();
	}

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

	// Update the weapon
	//if (hasWeapon)
	//{
	//	currentWeapon->SetOffset(GetWeaponOffset());
	//	currentWeapon->Update(deltaTime);
	//}
}

void Player::UpdateJoystickInput(float deltaTime)
{
	if (!Joystick::isConnected(0))
	{
#if _DEBUG
		printf("Warning: Joystick is disconnected.\n");
#endif
		PlayWithController = false;
		return;
	}

	if (Joystick::Joystick::isButtonPressed(0, 0))
	{
		StartAttack();
		return;
	}

	// TODO: No need to check this every time
	if (Joystick::hasAxis(0, Joystick::X) && Joystick::hasAxis(0, Joystick::Y))
	{
		// Get the axis position of the stick
		float x = Joystick::getAxisPosition(0, Joystick::X) / 100;
		float y = Joystick::getAxisPosition(0, Joystick::Y) / 100;

		// Dont move if the control is within its dead zone
		if (x < controls::JoystickDeadZone && x > -controls::JoystickDeadZone) x = 0;
		if (y < controls::JoystickDeadZone && y > -controls::JoystickDeadZone) y = 0;

		// Move the player if the stick has moved
		if (abs(x) > 0 || abs(y) > 0)
		{
			Move(movementSpeed * x * deltaTime, movementSpeed * y * deltaTime);
			
			return; // Prevent checking inputs from the dpad if the player is already moving with the stick
		}
	}

	// TODO: No need to check this every time
	if (Joystick::hasAxis(0, Joystick::PovX) && Joystick::hasAxis(0, Joystick::PovY))
	{
		float inputX = roundf(Joystick::getAxisPosition(0, Joystick::PovX) / 100);
		float inputY = -roundf(Joystick::getAxisPosition(0, Joystick::PovY) / 100);

		Vector2f dir = GetDirectionVector(
			inputY > 0,
			inputY < 0,
			inputX < 0,
			inputX > 0
		);

		Move(movementSpeed * dir.x * deltaTime, movementSpeed * dir.y * deltaTime);
	}
}

void Player::UpdateKeyboardInput(float deltaTime)
{
	if (Keyboard::isKeyPressed(controls::AttackButton))
	{
		StartAttack();
		return;
	}

	Vector2f dir = GetDirectionVector(
		Keyboard::isKeyPressed(controls::DownButton),
		Keyboard::isKeyPressed(controls::UpButton),
		Keyboard::isKeyPressed(controls::LeftButton),
		Keyboard::isKeyPressed(controls::RightButton)
	);

	Move(movementSpeed * dir.x * deltaTime, movementSpeed * dir.y * deltaTime);
}

Vector2i Player::GetDirectionVector(FacingDirections direction) const
{
	switch (direction)
	{
	case Player::Up:
		return { 0, -1 };
		break;
	default:
	case Player::Down:
		return { 0, 1 };
		break;
	case Player::Left:
		return { -1, 0 };
		break;
	case Player::Right:
		return { 1, 0 };
		break;
	}
}

Vector2f Player::GetDirectionVector(bool pressedDown, bool pressedUp, bool pressedLeft, bool pressedRight) const
{
	float directionX = 0, directionY = 0;

	if (pressedUp && pressedLeft)
		directionX = directionY = -diagonalSpeedMultiplier;
	else if (pressedDown && pressedRight)
		directionX = directionY = diagonalSpeedMultiplier;
	else if (pressedDown && pressedLeft)
	{
		directionX = -diagonalSpeedMultiplier;
		directionY = diagonalSpeedMultiplier;
	}
	else if (pressedUp && pressedRight)
	{
		directionX = diagonalSpeedMultiplier;
		directionY = -diagonalSpeedMultiplier;
	}
	else if (pressedRight)
		directionX = 1.f;
	else if (pressedLeft)
		directionX = -1.f;
	else if (pressedUp)
		directionY = -1.f;
	else if (pressedDown)
		directionY = 1.f;

	return { directionX, directionY };
}

Player::FacingDirections Player::GetDirectionEnum(const Vector2i& direction) const
{
	return GetDirectionEnum(direction.x, direction.y);
}

Player::FacingDirections Player::GetDirectionEnum(const Vector2f& direction) const
{
	return GetDirectionEnum(direction.x, direction.y);
}

Player::FacingDirections Player::GetDirectionEnum(int directionX, int directionY) const
{
	if (directionY < 0)
		return FacingDirections::Down;
	if (directionY > 0)
		return FacingDirections::Up;
	if (directionX > 0)
		return FacingDirections::Right;
	if (directionX < 0)
		return FacingDirections::Left;

#if _DEBUG
	printf("Warning: Can't get a direction if the player doesn't move.\n");
#endif
	return FacingDirections::Down;
}

Player::FacingDirections Player::GetDirectionEnum(float directionX, float directionY) const
{
	return GetDirectionEnum((int)directionX, (int)directionY);
}

void Player::ChangeState(States newState)
{
	// Don't change the state if it didn't actually changed
	if (currentState == newState)
		return;

	currentState = newState;
}

void Player::ChangeDirection(FacingDirections newDirection)
{
	// Don't change the facing direction if it didn't actually changed
	if (currentFacingDirection == newDirection)
		return;

	currentFacingDirection = newDirection;
}

void Player::UpdateAnimation()
{
	sprite.switchToAnimation(currentState | currentFacingDirection);
}

void Player::Move(float x, float y)
{
	// If the player didn't move, change to the idle state
	if (x == 0 && y == 0)
	{
		ChangeState(States::Idle);
		UpdateAnimation();
		return;
	}

	// If the player moves more horizontal than vertical, she will face either left or right
	else if (abs(x) > abs(y))
	{
		if (x > 0)
			ChangeDirection(FacingDirections::Right);
		else
			ChangeDirection(FacingDirections::Left);
	}

	// If the player moves more vertical than horizontal, she will face either up or down
	else
	{
		if (y > 0)
			ChangeDirection(FacingDirections::Down);
		else
			ChangeDirection(FacingDirections::Up);
	}

	// Change the state and update the animation
	ChangeState(States::Walking);
	UpdateAnimation();

	// Move the player
	Entity::Move(x, 0);
	ICollidable::UpdateXCollision(x);
	Entity::Move(0, y);
	ICollidable::UpdateYCollision(y);
}

void Player::Draw(RenderWindow& window)
{
	Entity::Draw(window);

	//if (hasWeapon)
		//currentWeapon->Draw(window);

	// Draws the hitbox
//#if _DEBUG
//	RectangleShape visualHitbox;
//	AABB aabb = GetAABBCollider();
//	visualHitbox.setSize((Vector2f)localHitbox.getSize());
//	visualHitbox.setFillColor(Color(255, 146, 0, 152));
//	visualHitbox.setPosition((float)aabb.left, (float)aabb.top);
//
//	window.draw(visualHitbox);
//#endif
}