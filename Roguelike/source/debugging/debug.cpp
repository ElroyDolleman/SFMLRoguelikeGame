#if _DEBUG
#include "stdafx.h"
#include "debugging\debug.h"

#include <stdarg.h>

Debug* Debug::instance = nullptr;

Debug::Debug()
{
	if (instance == nullptr)
		instance = this;
	else
		printf("Warning: There should only be 1 debug instance\n");
}

void Debug::WriteLine(string message)
{
	printf("%s\n", message.c_str());
}

void Debug::WriteLine(const char* format, ...)
{
	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);
}

void Debug::LoadDebugFont(string pathToFont)
{
	debugFont.loadFromFile(pathToFont + ".ttf");
}

void Debug::DrawScreenMessage(RenderWindow& window, string message, const Vector2f& position, Color color, int size)
{
	Text text = Text(message, instance->debugFont);
	text.setFillColor(color);
	text.setCharacterSize(size);
	text.setPosition(position.x + size, position.y + size);

	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(1.0f);

	window.draw(text);
}
void Debug::DrawScreenMessage(RenderWindow& window, string message, float xPosition, float yPosition, Color color, int size)
{
	DrawScreenMessage(window, message, { xPosition, yPosition }, color, size);
}
#endif