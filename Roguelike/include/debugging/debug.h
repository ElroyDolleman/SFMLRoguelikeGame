#pragma once

#if _DEBUG
class Debug
{
public:

	static Debug* instance;

	Debug();

	static void WriteLine(string message);
	static void WriteLine(const char* format, ...);

	// Loading a ttf file
	void LoadDebugFont(string pathToFont);

	static void DrawScreenMessage(RenderWindow& window, string message, const Vector2f& position, Color color = Color::White, int size = 6);
	static void DrawScreenMessage(RenderWindow& window, string message, float xPosition, float yPosition, Color color = Color::White, int size = 6);

private:

	Font debugFont;
};
#endif