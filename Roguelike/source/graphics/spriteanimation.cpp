#include "graphics\spriteanimation.h"

SpriteAnimation::SpriteAnimation(const Texture& texture, int sheetWidth, int sheetHeight, int tileWidth, int tileHeight)
	: SpriteSheet(texture, sheetWidth, sheetHeight, tileWidth, tileHeight)
{
}

SpriteAnimation::SpriteAnimation(const Texture& texture, const Vector2i& sheetSize, const Vector2i& tileSize)
	: SpriteSheet(texture, sheetSize, tileSize)
{
}

void SpriteAnimation::addAnimation(int animKey, float interval, int fromFrame, int toFrame)
{
#if _DEBUG
	if (fromFrame > toFrame)
	{
		printf("Warning: fromFrame needs to be lower than toFrame. %i is not lower than %i.\n", fromFrame, toFrame);
		int swap = fromFrame;
		fromFrame = toFrame;
		toFrame = swap;
	}
#endif

	// Fill the with a range from a frame to a frame
	vector<int> frames(toFrame + 1 - fromFrame);
	iota(frames.begin(), frames.end(), fromFrame);

	addAnimation(animKey, interval, frames);
}

void SpriteAnimation::addAnimation(int animKey, float interval, vector<int> frames)
{
	animations[animKey] = Animation(interval, frames);
	animationCount++;
}

void SpriteAnimation::update(float deltaTime)
{
#if _DEBUG
	if (animationCount == 0)
	{
		printf("Warning: Animation can't be updated if there are no animations.\n");
		return;
	}
#endif
	// If the animation is pause, stop updating it
	if (pause)
		return;

	timer += deltaTime * 1000.0f;
	Animation& animation = animations[currentAnimation];

	while (timer >= animation.interval)
	{
		timer -= animation.interval;

		if (!playBackwards)
			animation.nextFrame();
		else
			animation.previousFrame();

		setTileNumber(animation.getTileNumber());
	}
}

int SpriteAnimation::getAnimationCount()
{
	return animationCount;
}
