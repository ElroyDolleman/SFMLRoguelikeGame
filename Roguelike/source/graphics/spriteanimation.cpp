#include "graphics\spriteanimation.h"

SpriteAnimation::SpriteAnimation(const Texture& texture, int sheetWidth, int sheetHeight, int tileWidth, int tileHeight)
	: Tileset(texture, sheetWidth, sheetHeight, tileWidth, tileHeight)
{
}

SpriteAnimation::SpriteAnimation(const Texture& texture, const Vector2i& sheetSize, const Vector2i& tileSize)
	: Tileset(texture, sheetSize, tileSize)
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
	if (fromFrame == toFrame)
	{
		printf("Warning: fromFrame and toFrame are the same. Use the addAnimation overload that only takes a single frame instead.\n");
		addAnimation(animKey, interval, fromFrame);
		return;
	}
#endif

	vector<int> frames(toFrame + 1 - fromFrame);

	// Fill the with a range from a frame to a frame
	if (fromFrame == toFrame - 1)
		frames = { fromFrame, toFrame };
	else
		iota(frames.begin(), frames.end(), fromFrame);

	addAnimation(animKey, interval, frames);
}

void SpriteAnimation::addAnimation(int animKey, float interval, int singleFrame)
{
	animations[animKey] = Animation(interval, { singleFrame });
	animationCount++;
}

void SpriteAnimation::addAnimation(int animKey, float interval, vector<int> frames)
{
	animations[animKey] = Animation(interval, frames);
	animationCount++;
}

int SpriteAnimation::getCurrentAnimationKey() const
{
	return currentAnimation;
}

const SpriteAnimation::Animation& SpriteAnimation::getCurrentAnimation()
{
#if _DEBUG
	if (animations.size() == 0)
		printf("Error: Can't return the current animation when there are no animation. Game is going to crash.\n");
#endif
	return animations[currentAnimation];
}

void SpriteAnimation::switchToAnimation(int animKey)
{
	if (currentAnimation == animKey)
		return;

	currentAnimation = animKey;

	// Reset the timer
	timer = 0.0f;
	finishedPlaying = false;

	// Update the animation visually
	setTileNumber(animations[currentAnimation].getTileNumber());
	updateTextureRect();
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
	// If the animation is paused or finished, don't update it
	// If the current animation only has 1 frame, there is no need to update
	if (pause || finishedPlaying || animations[currentAnimation].getFramesCount() <= 1)
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

		// When the animation is at the last frame, and it doesn't loop, then the animation is finished
		if (!isLooping && animation.currentFrame == animation.getFramesCount() - 1)
			finishedPlaying = true;

		setTileNumber(animation.getTileNumber());
	}
}

int SpriteAnimation::getAnimationCount() const
{
	return animationCount;
}

bool SpriteAnimation::hasFinishedPlaying() const
{
	return finishedPlaying;
}

bool SpriteAnimation::IsLooping() const
{
	return isLooping;
}

void SpriteAnimation::SetLooping(bool loops)
{
	if (loops != isLooping)
	{
		isLooping = loops;
		finishedPlaying = false;
	}
}
