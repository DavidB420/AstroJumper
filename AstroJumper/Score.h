#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QGraphicsItem>

class Score : public QGraphicsTextItem
{
	Q_OBJECT

public:
	Score(QGraphicsTextItem *parent = 0);
	~Score();
	void increaseScore();
	int score;
};

#endif