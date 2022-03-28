#ifndef HIGHSCORESCENE_H
#define HIGHSCORESCENE_H

#define WINDOWS
//#define MACOS
//#define LINUX

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QLineEdit>
#include <QPushButton>
#include <fstream>
#ifdef WINDOWS //Checks if we are compiling for Windows
#include <windows.h>
#endif
#include <string>
#include <vector>
#include <QMessageBox>


class HighScoreScene : public QGraphicsScene
{
	Q_OBJECT

public:
	HighScoreScene(int score, QGraphicsScene *parent = 0);
	~HighScoreScene();
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
private slots:
	void submitName();
	void relaunchGame();
};

#endif