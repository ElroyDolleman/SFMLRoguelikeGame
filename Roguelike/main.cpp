#include "stdafx.h"
#include "managers\gamemanager.h"
#include "graphics\spriteanimation.h"

#if _DEBUG
#include "debugging\debug.h"
#endif

int main()
{
	RenderWindow window(VideoMode(256, 224), "Rogue");
	window.setFramerateLimit(60);

	window.setSize(sf::Vector2u(256*2, 224*2));

#if _DEBUG
	Debug debug;
	debug.LoadDebugFont("content\\fonts\\PixelFJVerdana12pt");
#endif

	Clock clock;
	GameManager* gameManager = new GameManager(window);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		float framerate = clock.getElapsedTime().asSeconds();
		clock.restart();

		window.clear();
		gameManager->Update(1.f / 60.f);
		gameManager->Draw();

		// Shows the fps on the screen
//#if _DEBUG
//		Debug::DrawScreenMessage(window, "fps " + to_string((int)roundf(1 / framerate)), 200, 0);
//#endif

		window.display();
	}

	delete gameManager;
	return 0;
}