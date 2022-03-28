/*--------------------------------------------------------------------------------
* Chidubem Dimanochie, Nathan Vuong
* 06/13/2022
* ICS4U1
* MainMenuScene.cpp
* Creates a main menu scene with its buttons and custom background.
*--------------------------------------------------------------------------------*/

#include "MainMenuScene.h"
#include "Game.h"

extern Game* game;

/**
* Initializes main menu scene with its buttons and custom background. 
* @param parent Inherits the QGraphicsScene class
*/
MainMenuScene::MainMenuScene(QGraphicsScene *parent) 
{
	//Creates Background image
	setSceneRect(0, 0, 800, 600);
	setBackgroundBrush(QBrush(QImage(":/images/Images/mainMenuBg.png")));

	//Create button when clicked sends user to Nightmare difficulty level
	QPushButton* nightmareButton = new QPushButton();
	QIcon nightmareIcon(":/images/Images/nightmareDifficultyIcon.png");
	nightmareButton->setIcon(nightmareIcon);
	nightmareButton->resize(150, 150);
	nightmareButton->move(500,300);
	nightmareButton->setIconSize(QSize(100, 100));
	QGraphicsProxyWidget* nightmareButtonProxy = addWidget(nightmareButton);
	connect(nightmareButton, SIGNAL(clicked()), this, SLOT(playNightmare()));

	//Create button when clicked sends user to Difficult difficulty level
	QPushButton* difficultButton = new QPushButton();
	QIcon difficultIcon(":/images/Images/difficultDifficultyIcon.png");
	difficultButton->setIcon(difficultIcon);
	difficultButton->resize(150, 150);
	difficultButton->setIconSize(QSize(100, 100));
	difficultButton->move(300, 300);
	QGraphicsProxyWidget* difficultButtonProxy = addWidget(difficultButton);
	connect(difficultButton, SIGNAL(clicked()), this, SLOT(playDifficult()));

	//Create button when clicked sends user to easy difficulty level
	QPushButton* easyButton = new QPushButton();
	QIcon easyIcon(":/images/Images/easyDifficultyIcon.png");
	easyButton->setIcon(easyIcon);
	easyButton->resize(150, 150);
	easyButton->setIconSize(QSize(100,100));
	easyButton->move(100, 300);
	QGraphicsProxyWidget* easyButtonProxy = addWidget(easyButton);
	connect(easyButton, SIGNAL(clicked()), this, SLOT(playEasy()));

	//Create button when clicked displays instructions on how to play the game
	QPushButton* instructionsButton = new QPushButton();
	QIcon instructionsIcon(":/images/Images/instructionIcon.png");
	instructionsButton->setIcon(instructionsIcon);
	instructionsButton->resize(100, 100);
	instructionsButton->setIconSize(QSize(50, 50));
	instructionsButton->move(225, 475);
	QGraphicsProxyWidget* instructionsButtonProxy = addWidget(instructionsButton);
	connect(instructionsButton, SIGNAL(clicked()), this, SLOT(showInstructions()));

	//Create button when clicked displays the credits for the game
	QPushButton* creditsButton = new QPushButton();
	QIcon creditsIcon(":/images/Images/creditsIcon.png");
	creditsButton->setIcon(creditsIcon);
	creditsButton->resize(100, 100);
	creditsButton->setIconSize(QSize(50,50));
	creditsButton->move(425, 475);
	QGraphicsProxyWidget* creditsButtonProxy = addWidget(creditsButton);
	connect(creditsButton, SIGNAL(clicked()), this, SLOT(showCredits()));

	//Plays background music while user is in MainMenuScene
	bgplayer = new QMediaPlayer(this);
	bgPlaylist = new QMediaPlaylist(this);
	bgPlaylist->addMedia(QUrl("qrc:sounds/Sounds/MainMenuMusic.mp3"));
	bgPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
	bgplayer->setPlaylist(bgPlaylist);
	bgplayer->play();
}

/**
* Sends user to Launch game with Nightmare Difficulty
*/
void MainMenuScene::playNightmare()
{
	//Stops playing the background music
	delete bgPlaylist;
	delete bgplayer;
	
	//Goes to the game in Nightmare mode
	game->launchGame(2); //0 - Easy, 1 - Difficult, 2 - Nightmare
}

/**
* Sends user to Launch game with Difficult Difficulty
*/
void MainMenuScene::playDifficult()
{	
	//Stops playing the background music
	delete bgPlaylist;
	delete bgplayer;
	
	//Goes to the game in Difficult mode
	game->launchGame(1); //0 - Easy, 1 - Difficult, 2 - Nightmare
}

/**
* Sends user to Launch game with easy Difficulty
*/
void MainMenuScene::playEasy()
{	
	//Stops the background music
	delete bgPlaylist;
	delete bgplayer;
	
	//Goes to the game in Easy mode
	game->launchGame(0); //0 - Easy, 1 - Difficult, 2 - Nightmare
}

/**
* Displays instructions for how to play the game
*/
void MainMenuScene::showInstructions()
{
	// Create message box that displays instructions
	QMessageBox* mBox = new QMessageBox();
	mBox->setText("Up Arrow - Jump\nLeft Arrow - Move Left\nRight Arrow - Move Right");
	mBox->setIcon(QMessageBox::Information);
	mBox->setWindowTitle("Instructions");
	mBox->show();
}

/**
* Displays credts for the game.
*/
void MainMenuScene::showCredits()
{
	// Create Message box that displays credits
	QMessageBox* mBox = new QMessageBox();
	mBox->setText("David Badiei - Team Leader/Programmer\nNathan Vuong - Sound/Documentation\nChidubem Dimanochie - Music/Main Menu\nAndrew Miceli - Graphics Design");
	mBox->setIcon(QMessageBox::Information);
	mBox->setWindowTitle("Credits");
	mBox->show();
}