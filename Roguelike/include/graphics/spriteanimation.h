#pragma once
#include "graphics\tileset.h"
#include "graphics\animation.h"

class SpriteAnimation : public Tileset
{
public:

	SpriteAnimation(const Texture& texture, int sheetWidth, int sheetHeight, int tileWidth, int tileHeight);
	SpriteAnimation(const Texture& texture, const Vector2i& sheetSize, const Vector2i& tileSize);

	void addAnimation(int animKey, Animation newAnimation);

	Animation& createAnimationFromTileNumbers(int animKey, float interval, const vector<int>& tileNumbers);
	Animation& createAnimationFromTileNumbers(int animKey, float interval, int fromTileNumber, int toTileNumber);
	Animation& createAnimationFromTileNumbers(int animKey, float interval, int singleTileNumber);

	int getCurrentAnimationKey() const;
	Animation& getCurrentAnimation();
	Animation& getAnimation(int animKey);

	void switchToAnimation(int animKey);

	void update(float deltaTime);

	int getAnimationCount() const;
	bool hasFinishedPlaying() const;

	bool pause = false;
	bool playBackwards = false;

	bool isLooping() const;
	void setLooping(bool loops);

protected:

	virtual void updateTextureRect() override;

	map<int, Animation> animations;
	int currentAnimationKey = 0;
	int animationCount = 0;

	float timer = 0.0f;
	bool finishedPlaying = false;
	bool loop = true;
};