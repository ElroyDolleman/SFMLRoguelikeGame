#include "stdafx.h"
#include "entities/entity.h"

Entity::Entity(SpriteAnimation sprite)
	: sprite(sprite)
{
}

void Entity::Move(float x, float y)
{
	sprite.move(x, y);
}

void Entity::Move(Vector2f direction)
{
	Move(direction.x, direction.y);
}

void Entity::MoveInAngle(float angle, float speed)
{
	Move(cos(angle) * speed, sin(angle) * speed);
}

void Entity::MoveTowards(Vector2f destination, float speed)
{
	MoveTowards(destination.x, destination.y, speed);
}

void Entity::MoveTowards(float destinationX, float destinationY, float speed)
{
	const Vector2f& pos = GetPosition();
	float angle = atan2(destinationY - pos.y, destinationX - pos.x);
	MoveInAngle(angle, speed);
}

void Entity::SetPosition(float x, float y)
{
	SetPosition({ x, y });
}

void Entity::SetPosition(const Vector2f& newPosition)
{
	sprite.setPosition(newPosition);
}

void Entity::SetXPosition(float x)
{
	SetPosition(x, sprite.getPosition().y);
}

void Entity::SetYPosition(float y)
{
	SetPosition(sprite.getPosition().x, y);
}

const Vector2f& Entity::GetPosition() const
{
	return sprite.getPosition();
}

void Entity::Draw(RenderWindow& window)
{
	window.draw(sprite);
}
