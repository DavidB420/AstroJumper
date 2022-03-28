/*--------------------------------------------------------------------------------
* David Badiei, Nathan Vuong
* 06/13/2022
* ICS4U1
* Game.cpp
* Creates Game object, stores the game scene with all of its children, such as the 
* player and the platforms
*-------------------------------------------------------------------------------*/

#include "Game.h"

/**
* Creates Game object and initializes all its values to its default settings
* @param parent Inherits QWidget class
*/
Game::Game(QWidget* parent)
{
	//Generate seed for the random number generator
	srand(time(0));

	//Fix the screen resolution and disable any scroll bars that may appear
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(800, 600);
	
	//Initialize current difficulty at its default position
	currentDifficulty = 0;
	
	//Show main menu screen
	mainMenuScene = new MainMenuScene();
	setScene(mainMenuScene);
}

/**
* Generate game platforms with random x coordinate
* @param startArr starting position in platform array
* @param stopArr ending position in platform array
* @param startY starting y coordinate
*/
void Game::generateGamePlatforms(int startArr, int stopArr, int startY)
{
	//Create new platform with random x coordinate and specified y coordinate
	platform[startArr] = new Platform();
	platform[startArr]->posX = rand() % 800 - 150 / 2;
	platform[startArr]->posY = startY;
	platform[startArr]->placePlatform();
	scene->addItem(platform[startArr]);

	/*Recursively generate game plaforms(while progressing through the platform array and decreasing y position)
	  Runs until it reaches the base case of the starting position equalling the ending position minus one*/  
	if (startArr < stopArr-1)
	{
		generateGamePlatforms(startArr + 1, stopArr, startY - 100);
	}
}

/**
* Closes game scene and loads high score scene
*/
void Game::loadHighScore()
{
	//Delete objects that handle the game music (dont want it playing in the high score menu)
	delete bgPlaylist;
	delete bgplayer;

	//If the current difficulty level is either Difficult or Nightmare, stop the projectile spawn timer
	if (currentDifficulty >= 1)
	{
		projectileSpawnTimer->stop();
	}

	//Create and set high score scene object
	hScoreScene = new HighScoreScene(score->score);
	setScene(hScoreScene);

	//Delete game scene object (along with its children)
	delete scene;
}


/**
* Launches the game scene with its selected difficulty level and sets up all of its children.
* @param gameDifficulty Selected difficulty level
*/
void Game::launchGame(int gameDifficulty)
{
	//Save difficulty level as the current difficulty level
	currentDifficulty = gameDifficulty;
	
	//Create and set game scene with its background
	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, 800, 600);
	scene->setBackgroundBrush(QBrush(QImage(":/images/Images/GameBg.png")));
	scene->setStickyFocus(true); //Make sure the focus is always on the player object
	setScene(scene);

	//Create score object with the current difficulty level and add it to the game scene
	score = new Score(currentDifficulty);
	score->setPos(0, 0);
	scene->addItem(score);

	//Generate the platforms
	generateGamePlatforms(0, 5, 460);

	//Create and add player object
	player = new Player(currentDifficulty);
	scene->addItem(player);

	//If the current difficulty level is either Difficult or Nightmare, create a timer that will spawn falling projectiles
	if (currentDifficulty >= 1)
	{
		projectileSpawnTimer = new QTimer(this);
		connect(projectileSpawnTimer, SIGNAL(timeout()), this, SLOT(projectileSpawn()));
		projectileSpawnTimer->start(2000);
	}
	
	//Initialize the background music
	bgplayer = new QMediaPlayer(this); //Creates the music player object
	bgPlaylist = new QMediaPlaylist(this); 	//Creates the music playlist object
	bgPlaylist->addMedia(QUrl("qrc:/sounds/Sounds/BGMusic.mp3")); //Add in the game music from the resource file
	bgPlaylist->setPlaybackMode(QMediaPlaylist::Loop); //Plays the music in a loop
	bgplayer->setPlaylist(bgPlaylist); //Set playlist
	bgplayer->play(); //Plays the game music
}

/**
* Spawn falling projectile projects with random x coordinate
*/
void Game::projectileSpawn()
{
	//Create projectile object
	projectile = new Projectile();

	//Give projectile object a random x coordinate and set its y coordinate to the top of the screen
	projectile->setPos(static_cast<qreal>(rand() % 800) + 1, 0);

	//Add projectile to game scene
	scene->addItem(projectile);
}