#include "stdafx.h"
#include "collision\aabb.h"
#include "..\..\include\collision\aabb.h"

AABB::AABB()
{
}

AABB::AABB(int x, int y, int width, int height)
{
	left = x;
	top = y;
	this->width = width;
	this->height = height;
}

AABB::~AABB()
{
}

int AABB::getXDepth(AABB box) const
{
	int minRight = min(left + width, box.left + box.width);
	int maxLeft = max(left, box.left);

	if (minRight > maxLeft)
		return minRight - maxLeft;
	return 0;
}

int AABB::getYDepth(AABB box) const
{
	int minTop = min(top + height, box.top + box.height);
	int maxBottom = max(top, box.top);

	if (minTop > maxBottom)
		return minTop - maxBottom;
	return 0;
}

bool AABB::isOnLeftOf(const AABB& box) const
{
	return getCenterX() < box.getCenterX();
}

bool AABB::isAbove(const AABB& box) const
{
	return getCenterY() < box.getCenterY();
}

int AABB::getCenterX() const
{
	return left + width / 2;
}

int AABB::getCenterY() const
{
	return top + height / 2;
}

Vector2i AABB::getCenter() const
{
	return Vector2i(getCenterX(), getCenterY());
}

int AABB::getRight() const
{
	return left + width;
}

int AABB::getBottom() const
{
	return top + height;
}

Vector2i AABB::getSize() const
{
	return Vector2i(width, height);
}
