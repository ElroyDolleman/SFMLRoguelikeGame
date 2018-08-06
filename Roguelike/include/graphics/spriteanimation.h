#pragma once
#include "graphics\tileset.h"

class SpriteAnimation : public Tileset
{
public:

	struct Animation
	{
		Animation() { }
		Animation(float interval, const vector<int>& frames)
		{
			this->interval = interval;
			this->frames = frames;
			framesCount = (int)frames.size();
		}

		// Stores the tile numbers. The animation will show each tile in order.
		vector<int> frames;

		int currentFrame = 0;
		float interval = 1000.0f;

		void nextFrame()
		{
			currentFrame++;
			if (currentFrame >= framesCount)
				currentFrame = 0;
		}

		void previousFrame()
		{
			currentFrame--;
			if (currentFrame < 0)
				currentFrame = framesCount - 1;
		}

		int getTileNumber() const
		{
			return frames[currentFrame];
		}

		int getFramesCount() { return framesCount; }
		private:
			int framesCount;
	};

	SpriteAnimation(const Texture& texture, int sheetWidth, int sheetHeight, int tileWidth, int tileHeight);
	SpriteAnimation(const Texture& texture, const Vector2i& sheetSize, const Vector2i& tileSize);

	void addAnimation(int animKey, float interval, int fromFrame, int toFrame);
	void addAnimation(int animKey, float interval, vector<int> frames);

	int getCurrentAnimationKey() const;

	void switchToAnimation(int animKey);

	void update(float deltaTime);

	int getAnimationCount();

	bool pause = false;
	bool playBackwards = false;

protected:

	map<int, Animation> animations;
	int currentAnimation = 0;
	int animationCount = 0;

	float timer = 0.0f;
};