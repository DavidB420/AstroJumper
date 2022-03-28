/*--------------------------------------------------------------------------------
* David Badiei, Nathan Vuong
* 06/13/2022
* ICS4U1
* Projectile.h
* Header (definition file) for Projectile object
*-------------------------------------------------------------------------------*/

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
private:
	QMediaPlayer* gunSfx;
	QMediaPlayer* deathSfx;
	bool hitPlayer;
private slots:
	int move();
};

#endif