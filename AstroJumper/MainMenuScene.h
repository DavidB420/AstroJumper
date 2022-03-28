#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QPushButton>
#include <QIcon>

class MainMenuScene : public QGraphicsScene
{
	Q_OBJECT

public:
	MainMenuScene(QGraphicsScene* parent = 0);
	~MainMenuScene();
private slots:
	void playNightmare();
	void playDifficult();
	void playEasy();
	void showInstructions();
	void showCredits();
};

#endif