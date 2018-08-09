#include "entities\enemies\slime.h"

Slime::Slime(SpriteAnimation sprite)
	: Enemy(sprite)
{
	//this->sprite.addAnimation(LeftAnimation, 500.0f, 0, 1);
	//this->sprite.addAnimation(RightAnimation, 500.0f, 2, 3);

	localHitbox = { 3, 5, 10, 9 };
}

AABB Slime::GetAABBCollider() const
{
	AABB globalHitbox = localHitbox;
	const Vector2f& pos = GetPosition();

	globalHitbox.left = static_cast<int>(roundf(pos.x)) + localHitbox.left;
	globalHitbox.top = static_cast<int>(roundf(pos.y)) + localHitbox.top;

	return globalHitbox;
}

void Slime::SetCollidablePositionX(float xPos)
{
	SetXPosition(xPos - localHitbox.left);
}

void Slime::SetCollidablePositionY(float yPos)
{
	SetYPosition(yPos - localHitbox.top);
}

bool Slime::IntersectsHurtbox(const vector<AABB>& damageBoxes) const
{
	return false;
}

void Slime::Damage(int damage)
{
	health -= damage;
}

void Slime::Update(float deltaTime)
{
	// Update the sprite animation
	//sprite.update(deltaTime);

	if (hasTarget)
	{
#if _DEBUG
		if (target == nullptr)
			printf("Warning: Slime is trying to follow a nullptr target.\n");
		else
		{
#endif
			/*Vector2f targetCenter = (Vector2f)target->GetAABBHurtbox().getCenter();
			Vector2f myCenter = (Vector2f)localHitbox.getCenter();

			MoveTowards(targetCenter.x - myCenter.x, targetCenter.y - myCenter.y, speed * deltaTime);*/
#if _DEBUG
		}
#endif
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

void Slime::Draw(RenderWindow& window)
{
	Entity::Draw(window);

	// Draw Hitbox
	/*#if _DEBUG
	RectangleShape visualHitbox;
	AABB aabb = GetAABBCollider();
	visualHitbox.setSize((Vector2f)localHitbox.getSize());
	visualHitbox.setFillColor(Color(255, 0, 0, 200));
	visualHitbox.setPosition((float)aabb.left, (float)aabb.top);

	window.draw(visualHitbox);
	#endif*/
}