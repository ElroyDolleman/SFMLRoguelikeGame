#pragma once
#include "graphics\spriteanimation.h"

class Entity
{
public:

	Entity(SpriteAnimation sprite);

	virtual void Move(float x, float y);
	virtual void Move(Vector2f direction);

	virtual void MoveInAngle(float angle, float speed);
	virtual void MoveTowards(Vector2f destination, float speed);

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const Vector2f& newPosition);
	virtual void SetXPosition(float x);
	virtual void SetYPosition(float y);

	const Vector2f& GetPosition() const;

	//virtual bool Intersects() const = 0;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(RenderWindow& window);

protected:

	SpriteAnimation sprite;

private:


};