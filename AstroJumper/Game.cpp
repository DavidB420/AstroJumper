#include "Game.h"

Game::Game(QWidget* parent)
{
	srand(time(0));

	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, 800, 600);
	scene->setStickyFocus(true);
	setScene(scene);

	player = new Player();
	scene->addItem(player);

	int currentY = 460;
	for (int i = 0; i <= 5; i++)
	{
		platform = new Platform();
		platform->posX = rand() % 800 - 150 / 2;
		platform->posY = currentY;
		platform->placePlatform();
		scene->addItem(platform);
		platform = new Platform();
		platform->posX = rand() % 800 - 150 / 2;
		platform->posY = currentY;
		platform->placePlatform();
		scene->addItem(platform);
		currentY -= 100;
	}

}

Game::~Game()
{
}

void Game::platformSpawn()
{
	platform = new Platform();
	platform->posX = rand() % 800 + 1;
	scene->addItem(platform);
}
