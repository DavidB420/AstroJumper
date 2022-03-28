/*--------------------------------------------------------------------------------
* Chidubem Dimanochie, Nathan Vuong
* 06/13/2022
* ICS4U1
* MainMenuScene.h
* Header (definition file) for MainMenuScene object
*-------------------------------------------------------------------------------*/

#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QPushButton>
#include <QIcon>
#include <QMediaPlayer>
#include <QMediaPlaylist>


class MainMenuScene : public QGraphicsScene
{
	Q_OBJECT

public:
	MainMenuScene(QGraphicsScene* parent = 0);
private:
	QMediaPlayer* bgplayer;
	QMediaPlaylist* bgPlaylist;
private slots:
	void playNightmare();
	void playDifficult();
	void playEasy();
	void showInstructions();
	void showCredits();
};

#endif