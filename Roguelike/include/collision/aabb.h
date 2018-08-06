#pragma once

class AABB : public IntRect
{
public:

	AABB();
	AABB(int x, int y, int width, int height);
	~AABB();

	int getXDepth(AABB box) const;
	int getYDepth(AABB box) const;

	bool isOnLeftOf(const AABB& box) const;
	bool isAbove(const AABB& box) const;

	int getCenterX() const;
	int getCenterY() const;
	Vector2i getCenter() const;

	int getRight() const;
	int getBottom() const;

	Vector2i getSize() const;

private:


};