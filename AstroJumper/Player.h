/*--------------------------------------------------------------------------------
* David Badiei, Nathan Vuong
* 06/13/2022
* ICS4U1
* Player.h
* Header (definition file) for Player object
*-------------------------------------------------------------------------------*/

#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QTimer>
#include <QEvent>
#include <QDebug>
#include <math.h>
#include "Platform.h"
#include "os.h"
#include <QMediaPlayer>
//#include "Game.h"

#define VELOCITY 7.00f
#define PI 2*acos(0.0)

class Player : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	Player(int difficulty, QGraphicsPixmapItem *parent = 0);
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
	int dx = 0, dy = 0, xPos, yPos, currentDifficulty;
	float angle, prevAngle;
private:
	float time = 0;
	bool firstJump, deathSfxPlayed;
	QGraphicsItem* playerPlatform;
	QTimer* timer = NULL;
	QMediaPlayer* jumpSfx;
	QMediaPlayer* deathSfx;
	QMediaPlayer* walkSfx;

private slots:
	int playerPhysics();
};

#endif