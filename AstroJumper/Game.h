#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "Player.h"
#include "Platform.h"
#include "Projectile.h"
#include "Score.h"
#include "HighScoreScene.h"
#include <time.h>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "MainMenuScene.h"

class Game : public QGraphicsView
{
	Q_OBJECT

public:
	Game(QWidget *parent = 0);
	~Game();
	int currentDifficulty;
	QGraphicsScene* scene;
	Player* player;
	Platform* platform[5] = { NULL,NULL,NULL,NULL,NULL };
	Projectile* projectile;
	Score* score;
	HighScoreScene* hScoreScene;
	QTimer* projectileSpawnTimer;
	MainMenuScene* mainMenuScene;
	void generateGamePlatforms(int startArr, int stopArr, int startY);
	void loadHighScore();
	void launchGame(int gameDifficulty);
private:
	QMediaPlayer* bgplayer;
	QMediaPlaylist* bgPlaylist;
private slots:
	void projectileSpawn();
	
};

#endif