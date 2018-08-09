#pragma once

struct Frame
{
public:

	Frame()
	{
		id = ++nextID;
		//printf("ID = %i\n", id);
	}
	Frame(const IntRect& rect) 
		: Frame()
	{ 
		textureRect = rect;
	}
	Frame(int x, int y, int width, int height)
		: Frame(IntRect(x, y, width, height))
	{
	}

	IntRect textureRect;

	int GetID() const { return id; }

private:

	static int nextID;
	int id = 0;
};

struct Animation
{
public:

	Animation()
	{
	}

	Animation(Frame singleFrame, float interval = 100.f)
	{
		this->interval = interval;
		frames.push_back(singleFrame);

		framesCount = 1;
	}

	Animation(vector<Frame>& frames, float interval = 100.f)
	{
		this->interval = interval;
		this->frames = frames;

		framesCount = (int)frames.size();

#if _DEBUG
		if (framesCount == 0)
			printf("Warning: An animation was created without any frames.\n");
#endif
	}

	/// <summary> The amount of time (in miliseconds) it takes to go to the next frame </summary>
	float interval = 100.f;

	/// <summary> Adds a new frame to the animation. </summary>
	inline void AddFrame(Frame frame)
	{
		frames.push_back(frame);
		framesCount++;
	}

	int FramesCount() const { return framesCount; }

	/// <summary> Goes to the next frame. It loops back to the first frame when it goes past the last frame. </summary>
	/// <returns> The frame number. </returns>
	int NextFrame()
	{
		currentFrame++;
		if (currentFrame >= framesCount)
			currentFrame = 0;
		return currentFrame;
	}

	/// <summary> Goes to the previous frame. It loops back to the last frame when it goes past the first one. </summary>
	/// <returns> The frame number. </returns>
	int PreviousFrame()
	{
		currentFrame--;
		if (currentFrame < 0)
			currentFrame = framesCount - 1;
		return currentFrame;
	}

	void GoToFrame(int frameNumber) { currentFrame = frameNumber % framesCount; }

	void Reset() { currentFrame = 0; }

	bool IsAtLastFrame() const { return currentFrame == framesCount - 1; }

	Frame& GetCurrentFrame() { return frames[currentFrame]; }
	Frame& GetFrame(int frameNumber) { return frames[min(framesCount-1, max(0, frameNumber))]; }
	vector<Frame>& GetAllFrames() { return frames;  }

	int GetCurrentFrameNumber() const { return currentFrame; }

private:

	vector<Frame> frames;

	int framesCount = 0;
	int currentFrame = 0;
};