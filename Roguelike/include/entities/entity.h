#pragma once
#include "graphics\spriteanimation.h"

class Entity
{
public:

	Entity(SpriteAnimation sprite);

	virtual void Move(float x, float y);
	virtual void Move(Vector2f direction);

	virtual void MoveInAngle(float angle, float speed);

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const Vector2f& newPosition);

	virtual bool Intersects() const = 0;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(RenderWindow& window);

protected:

	SpriteAnimation sprite;

private:


};