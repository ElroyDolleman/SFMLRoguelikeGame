#include "stdafx.h"
#include "managers/gamemanager.h"

int main()
{
	RenderWindow window(VideoMode(256, 224), "Rogue");
	GameManager* gameManager = new GameManager(window);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		gameManager->Update(0);
		gameManager->Draw();
		window.display();
	}

	delete gameManager;
	return 0;
}