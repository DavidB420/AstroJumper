#include "MainMenuScene.h"
#include "Game.h"

extern Game* game;

MainMenuScene::MainMenuScene(QGraphicsScene *parent)
{
	setSceneRect(0, 0, 800, 600);
	setBackgroundBrush(QBrush(QImage(":/images/Images/mainMenuBg.png")));

	QPushButton* nightmareButton = new QPushButton();
	QIcon nightmareIcon(":/images/Images/nightmareDifficultyIcon.png");
	nightmareButton->setIcon(nightmareIcon);
	nightmareButton->resize(150, 150);
	nightmareButton->move(500,300);
	nightmareButton->setIconSize(QSize(100, 100));
	QGraphicsProxyWidget* nightmareButtonProxy = addWidget(nightmareButton);
	connect(nightmareButton, SIGNAL(clicked()), this, SLOT(playNightmare()));

	QPushButton* difficultButton = new QPushButton();
	QIcon difficultIcon(":/images/Images/difficultDifficultyIcon.png");
	difficultButton->setIcon(difficultIcon);
	difficultButton->resize(150, 150);
	difficultButton->setIconSize(QSize(100, 100));
	difficultButton->move(300, 300);
	QGraphicsProxyWidget* difficultButtonProxy = addWidget(difficultButton);
	connect(difficultButton, SIGNAL(clicked()), this, SLOT(playDifficult()));

	QPushButton* easyButton = new QPushButton();
	QIcon easyIcon(":/images/Images/easyDifficultyIcon.png");
	easyButton->setIcon(easyIcon);
	easyButton->resize(150, 150);
	easyButton->setIconSize(QSize(100,100));
	easyButton->move(100, 300);
	QGraphicsProxyWidget* easyButtonProxy = addWidget(easyButton);
	connect(easyButton, SIGNAL(clicked()), this, SLOT(playEasy()));

	QPushButton* instructionsButton = new QPushButton();
	QIcon instructionsIcon(":/images/Images/instructionIcon.png");
	instructionsButton->setIcon(instructionsIcon);
	instructionsButton->resize(100, 100);
	instructionsButton->setIconSize(QSize(50, 50));
	instructionsButton->move(225, 475);
	QGraphicsProxyWidget* instructionsButtonProxy = addWidget(instructionsButton);
	connect(instructionsButton, SIGNAL(clicked()), this, SLOT(showInstructions()));

	QPushButton* creditsButton = new QPushButton();
	QIcon creditsIcon(":/images/Images/creditsIcon.png");
	creditsButton->setIcon(creditsIcon);
	creditsButton->resize(100, 100);
	creditsButton->setIconSize(QSize(50,50));
	creditsButton->move(425, 475);
	QGraphicsProxyWidget* creditsButtonProxy = addWidget(creditsButton);
	connect(creditsButton, SIGNAL(clicked()), this, SLOT(showCredits()));

	bgplayer = new QMediaPlayer(this);
	bgPlaylist = new QMediaPlaylist(this);
	bgPlaylist->addMedia(QUrl("qrc:sounds/Sounds/MainMenuMusic.mp3"));
	bgPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
	bgplayer->setPlaylist(bgPlaylist);
	bgplayer->play();
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::playNightmare()
{
	delete bgPlaylist;
	delete bgplayer;
	game->launchGame(2); //0 - Easy, 1 - Difficult, 2 - Nightmare
}

void MainMenuScene::playDifficult()
{	
	delete bgPlaylist;
	delete bgplayer;
	game->launchGame(1); //0 - Easy, 1 - Difficult, 2 - Nightmare
}

void MainMenuScene::playEasy()
{	
	delete bgPlaylist;
	delete bgplayer;
	game->launchGame(0); //0 - Easy, 1 - Difficult, 2 - Nightmare
}

void MainMenuScene::showInstructions()
{
	QMessageBox* mBox = new QMessageBox();
	mBox->setText("Up Arrow - Jump\nLeft Arrow - Move Left\nRight Arrow - Move Right");
	mBox->setIcon(QMessageBox::Information);
	mBox->setWindowTitle("Instructions");
	mBox->show();
}

void MainMenuScene::showCredits()
{
	QMessageBox* mBox = new QMessageBox();
	mBox->setText("David Badiei - Team Leader/Programmer\nNathan Vuong - Sound/Documentation\nChidubem Dimanochie - Music/Main Menu\nAndrew Miceli - Graphics Design");
	mBox->setIcon(QMessageBox::Information);
	mBox->setWindowTitle("Credits");
	mBox->show();
}