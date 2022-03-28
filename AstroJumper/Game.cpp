#include "Game.h"

Game::Game(QWidget* parent)
{
	srand(time(0));
	
	launchGame();
}

Game::~Game()
{
}

void Game::generateGamePlatforms(int startArr, int stopArr, int startY)
{
	platform[startArr] = new Platform();
	platform[startArr]->posX = rand() % 800 - 150 / 2;
	platform[startArr]->posY = startY;
	platform[startArr]->placePlatform();
	scene->addItem(platform[startArr]);

	if (startArr < stopArr-1)
	{
		generateGamePlatforms(startArr + 1, stopArr, startY - 100);
	}
}

void Game::loadHighScore()
{
	delete bgPlaylist;
	delete bgplayer;
	projectileSpawnTimer->stop();
	hScoreScene = new HighScoreScene(score->score);
	setScene(hScoreScene);
	delete scene;
}

void Game::launchGame()
{
	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, 800, 600);
	scene->setBackgroundBrush(QBrush(QImage(":/images/Images/GameBg.png")));
	scene->setStickyFocus(true);
	setScene(scene);

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(800, 600);

	score = new Score();
	score->setPos(0, 0);
	scene->addItem(score);

	generateGamePlatforms(0, 5, 460);

	player = new Player();
	scene->addItem(player);

	projectileSpawnTimer = new QTimer(this);
	connect(projectileSpawnTimer, SIGNAL(timeout()), this, SLOT(projectileSpawn()));
	projectileSpawnTimer->start(2000);

	bgplayer = new QMediaPlayer(this);
	bgPlaylist = new QMediaPlaylist(this);
	bgPlaylist->addMedia(QUrl("qrc:/sounds/Sounds/BGMusic.mp3"));
	bgPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
	bgplayer->setPlaylist(bgPlaylist);
	bgplayer->play();
}

void Game::projectileSpawn()
{
	projectile = new Projectile();
	projectile->setPos(static_cast<qreal>(rand() % 800) + 1, 0);
	scene->addItem(projectile);
}