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
	sprite.move(direction);
}

void Entity::MoveInAngle(float angle, float speed)
{
	sprite.move(cos(angle) * speed, sin(angle) * speed);
}

void Entity::SetPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Entity::SetPosition(const Vector2f& newPosition)
{
	sprite.setPosition(newPosition);
}

void Entity::Draw(RenderWindow& window)
{
	window.draw(sprite);
}
