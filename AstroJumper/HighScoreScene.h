/*--------------------------------------------------------------------------------
* David Badiei, Nathan Vuong
* 06/13/2022
* ICS4U1
* HighScoreScene.h
* Header (definition file) for HighScoreScene object
*-------------------------------------------------------------------------------*/

#ifndef HIGHSCORESCENE_H
#define HIGHSCORESCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QLineEdit>
#include <QPushButton>
#include <fstream>
#include "os.h"
#ifdef WINDOWS //Checks if we are compiling for Windows
#include <windows.h>
#endif
#include <string>
#include <vector>
#include <QMessageBox>

using namespace std; //Access the std namespace (we can access fstream)

class HighScoreScene : public QGraphicsScene
{
	Q_OBJECT

public:
	HighScoreScene(int score, QGraphicsScene *parent = 0);
	QGraphicsTextItem* top5PlayersScore[2][5];
	QLineEdit* nameEntry;
	QGraphicsProxyWidget* nameEntryProxy;
	QPushButton* submitNameButton;
	QGraphicsProxyWidget* submitNameButtonProxy;
	QString returnPlayerNameOrScore(int index, bool getName);
	int getPosInFile(int score);
	int getNumOfLines();
	int currentScore;
	void createPlayAgainButton();
private:
	void loadHighScoreFile(ifstream& scoreFile);
private slots:
	void submitName();
	void relaunchGame();
};

#endif