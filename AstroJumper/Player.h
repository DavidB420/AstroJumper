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
#include <QMediaPlayer>
//#include "Game.h"

#define VELOCITY 7.00f
#define PI 2*acos(0.0)

class Player : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	Player(QGraphicsPixmapItem *parent = 0);
	~Player();
	void keyPressEvent(QKeyEvent* event);
	int dx = 0, dy = 0, xPos, yPos;
	float angle, prevAngle;
private:
	float time = 0;
	bool firstJump, deathSfxPlayed;
	QGraphicsItem* playerPlatform;
	QTimer* timer = NULL;
	QTimer* keyTimer = NULL;
	QMediaPlayer* jumpSfx;
	QMediaPlayer* deathSfx;

private slots:
	int playerPhysics();
};

#endif