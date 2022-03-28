#ifndef HIGHSCORESCENE_H
#define HIGHSCORESCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QLineEdit>
#include <QPushButton>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>
#include <QMessageBox>

class HighScoreScene : public QGraphicsScene
{
	Q_OBJECT

public:
	HighScoreScene(int score, QGraphicsScene *parent = 0);
	~HighScoreScene();
	QGraphicsTextItem* top5Players[5];
	QGraphicsTextItem* top5PlayersScore[5];
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