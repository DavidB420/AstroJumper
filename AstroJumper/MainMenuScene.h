#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <QObject>
#include <QGraphicsScene>

class MainMenuScene : public QGraphicsScene
{
	Q_OBJECT

public:
	MainMenuScene(QGraphicsScene *parent);
	~MainMenuScene();
};

#endif