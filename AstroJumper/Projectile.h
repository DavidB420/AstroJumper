#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include "Player.h"
#include <QMediaPlayer>

class Projectile : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	Projectile(QGraphicsPixmapItem *parent = 0);
	~Projectile();
private:
	QMediaPlayer* gunSfx;
	QMediaPlayer* deathSfx;
	bool hitPlayer;
private slots:
	int move();
};

#endif