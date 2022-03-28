/*--------------------------------------------------------------------------------
* David Badiei
* 06/13/2022
* ICS4U1
* Score.h
* Header (definition file) for Score object
*-------------------------------------------------------------------------------*/

#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QGraphicsItem>

class Score : public QGraphicsTextItem
{
	Q_OBJECT

public:
	Score(int difficulty, QGraphicsTextItem *parent = 0);
	void increaseScore();
	int score, currentDifficulty;
};

#endif