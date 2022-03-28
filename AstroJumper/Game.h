#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"
#include "Platform.h"
#include <time.h>

class Game : public QGraphicsView
{
	Q_OBJECT

public:
	Game(QWidget *parent = 0);
	~Game();
	QGraphicsScene* scene;
	Player* player;
	Platform* platform = NULL;
private slots:
	void platformSpawn();
};

#endif