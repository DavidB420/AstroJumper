#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include <QEvent>
#include <math.h>

#define VELOCITY 5.00f
#define PI 3.14159265

class Player : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Player(QGraphicsRectItem *parent = 0);
	~Player();
	void keyPressEvent(QKeyEvent* event);
	void createTimer(int theta,int speed);
	int dx, dy;
	float angle;
private:
	float time = 0;
	QTimer* timer = NULL;
	QTimer* keyTimer = NULL;
private slots:
	void jump();
};

#endif