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
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::playNightmare()
{
	game->launchGame(2); //0 - Easy, 1 - Difficult, 2 - Nightmare

}

void MainMenuScene::playDifficult()
{
	game->launchGame(1); //0 - Easy, 1 - Difficult, 2 - Nightmare

}

void MainMenuScene::playEasy()
{
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
	mBox->setText("David Lead Programmer\nNathan sound designer\nChidubem Music composer\nAndrew lead illustrator");
	mBox->setIcon(QMessageBox::Information);
	mBox->setWindowTitle("Credit");
	mBox->show();
}