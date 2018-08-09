#include "graphics\spriteanimation.h"

SpriteAnimation::SpriteAnimation(const Texture& texture, int sheetWidth, int sheetHeight, int tileWidth, int tileHeight)
	: Tileset(texture, sheetWidth, sheetHeight, tileWidth, tileHeight)
{
}

SpriteAnimation::SpriteAnimation(const Texture& texture, const Vector2i& sheetSize, const Vector2i& tileSize)
	: Tileset(texture, sheetSize, tileSize)
{
}

void SpriteAnimation::addAnimation(int animKey, Animation newAnimation)
{
	animations[animKey] = newAnimation;
	animationCount++;
}

Animation& SpriteAnimation::createAnimationFromTileNumbers(int animKey, float interval, const vector<int>& tileNumbers)
{
#if _DEBUG
	if (tileNumbers.size() == 0)
		throw exception("Cannot create an animation from tile numbers without tile numbers.");
#endif

	// Add the first frame
	Animation newAnimation = Animation(Frame(tileNumberToRect(tileNumbers[0])), interval);

	// Add every other frame
	for (int i = 1; i < tileNumbers.size(); i++)
		newAnimation.AddFrame(Frame(tileNumberToRect(tileNumbers[i])));

	// Add the animation to the list and return it
	addAnimation(animKey, newAnimation);
	return animations[animKey];
}

Animation& SpriteAnimation::createAnimationFromTileNumbers(int animKey, float interval, int fromTileNumber, int toTileNumber)
{
#if _DEBUG
	if (fromTileNumber > toTileNumber)
	{
		printf("Warning: fromTileNumber needs to be lower than toTileNumber. %i is not lower than %i.\n", fromTileNumber, toTileNumber);
		int swap = fromTileNumber;
		fromTileNumber = toTileNumber;
		toTileNumber = swap;
	}
	if (fromTileNumber == toTileNumber)
	{
		printf("Warning: fromTileNumber and toTileNumber are the same. Use the createAnimationFromTileNumbers overload that only takes a single frame instead.\n");
		return createAnimationFromTileNumbers(animKey, interval, fromTileNumber);
	}
#endif

	vector<int> frames(toTileNumber + 1 - fromTileNumber);

	// Fill the with a range from a frame to a frame
	if (fromTileNumber == toTileNumber - 1)
		frames = { fromTileNumber, toTileNumber };
	else
		iota(frames.begin(), frames.end(), fromTileNumber);

	return createAnimationFromTileNumbers(animKey, interval, frames);
}

Animation& SpriteAnimation::createAnimationFromTileNumbers(int animKey, float interval, int singleTileNumber)
{
	Animation newAnimation = Animation(Frame(tileNumberToRect(singleTileNumber)), interval);

	addAnimation(animKey, newAnimation);
	return animations[animKey];
}

int SpriteAnimation::getCurrentAnimationKey() const
{
	return currentAnimationKey;
}

Animation& SpriteAnimation::getCurrentAnimation()
{
	return getAnimation(currentAnimationKey);
}

Animation& SpriteAnimation::getAnimation(int animKey)
{
#if _DEBUG
	if (animations.size() == 0)
		throw exception("Can't return the animation with key %i when there are no animation. Game is going to crash.\n", animKey);

	map<int, Animation>::iterator it = animations.find(animKey);
	if (it == animations.end())
		throw exception("Can't return the animation with key %i because it does not exists\n", animKey);
#endif
	return animations[animKey];
}

void SpriteAnimation::switchToAnimation(int animKey)
{
	if (currentAnimationKey == animKey)
		return;

	animations[currentAnimationKey].Reset();
	currentAnimationKey = animKey;

	// Reset the timer
	timer = 0.0f;
	finishedPlaying = false;

	// Update the animation visually
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
	map<int, Animation>::iterator it = animations.find(currentAnimationKey);
	if (it == animations.end())
	{
		printf("Warning: Current animation does not exists\n");
		return;
	}
#endif
	// If the animation is paused or finished, don't update it
	// If the current animation only has 1 frame, there is no need to update
	if (pause || finishedPlaying || animations[currentAnimationKey].FramesCount() <= 1)
		return;

	timer += deltaTime * 1000.0f;
	Animation& animation = animations[currentAnimationKey];

	while (timer >= animation.interval)
	{
		timer -= animation.interval;

		if (!playBackwards)
			animation.NextFrame();
		else
			animation.PreviousFrame();

		// When the animation is at the last frame, and it doesn't loop, then the animation is finished
		if (!loop && animation.IsAtLastFrame())
			finishedPlaying = true;

		updateTextureRect();
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

bool SpriteAnimation::isLooping() const
{
	return loop;
}

void SpriteAnimation::setLooping(bool loops)
{
	if (loops != loop)
	{
		loop = loops;
		finishedPlaying = false;
	}
}

void SpriteAnimation::updateTextureRect()
{
	// Use the base updateTextureRect function if there are no animations
	if (animationCount == 0)
		Tileset::updateTextureRect();

#if _DEBUG
	map<int, Animation>::iterator it = animations.find(currentAnimationKey);
	if (it == animations.end()) 
	{
		printf("Warning: Can't update texture rect because the current animation does not exists.\n");
		return;
	}
#endif

	// Get the texture rect from the current frame
	setTextureRect(animations[currentAnimationKey].GetCurrentFrame().textureRect);
}
