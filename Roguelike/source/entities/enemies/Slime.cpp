#include "entities\enemies\slime.h"

Slime::Slime(SpriteAnimation sprite)
	: Enemy(sprite)
{
	this->sprite.addAnimation(LeftAnimation, 500.0f, 0, 1);
	this->sprite.addAnimation(RightAnimation, 500.0f, 2, 3);

	localHitbox = { 3, 5, 10, 9 };
}

AABB Slime::GetAABBCollider() const
{
	AABB globalHitbox = localHitbox;
	const Vector2f& pos = GetPosition();

	globalHitbox.left = (int)pos.x + localHitbox.left;
	globalHitbox.top = (int)pos.y + localHitbox.top;

	return globalHitbox;
}

void Slime::SetCollidablePositionX(float xPos)
{
	SetXPosition(xPos);
}

void Slime::SetCollidablePositionY(float yPos)
{
	SetYPosition(yPos);
}

bool Slime::IntersectsHurtbox() const
{
	return false;
}

AABB Slime::GetAABBHurtbox() const
{
	return GetAABBCollider();
}

void Slime::Damage(int damage)
{
	health -= damage;
}

void Slime::Update(float deltaTime)
{
	// Update the sprite animation
	sprite.update(deltaTime);

	if (hasTarget)
	{
#if _DEBUG
		if (target == nullptr)
			printf("Warning: Slime is trying to follow a nullptr target.\n");
		else
#endif
		MoveTowards((Vector2f)target->GetAABBHurtbox().getCenter(), speed * deltaTime);
	}
}

void Slime::Move(float x, float y)
{
	this->sprite.switchToAnimation(x < 0 ? LeftAnimation : RightAnimation);

	Entity::Move(x, 0);
	ICollidable::UpdateXCollision(x);
	Entity::Move(0, y);
	ICollidable::UpdateYCollision(y);
}

void Slime::MoveTowards(Vector2f destination, float speed)
{
	Entity::MoveTowards(destination, speed);
}

void Slime::SetTarget(IDamageable* target)
{
	hasTarget = true;
	this->target = target;
}

void Slime::LoseTarget()
{
	target = nullptr;
	hasTarget = false;
}