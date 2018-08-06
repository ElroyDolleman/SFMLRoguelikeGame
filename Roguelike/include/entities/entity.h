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
	virtual void MoveTowards(float destinationX, float destinationY, float speed);

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const Vector2f& newPosition);
	virtual void SetXPosition(float x);
	virtual void SetYPosition(float y);

	virtual void SetRotation(float rotation);
	virtual void Rotate(float amount);

	const Vector2f& GetPosition() const;
	float GetRotation() const;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(RenderWindow& window);

protected:

	SpriteAnimation sprite;

private:


};