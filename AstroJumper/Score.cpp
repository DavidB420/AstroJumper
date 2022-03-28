#include "Score.h"
#include <QFont>

Score::Score(QGraphicsTextItem* parent)
{
	score = 0;
	setPlainText(QString("Score = ") + QString::number(score));
	setDefaultTextColor(Qt::white);
	setFont(QFont("Arial", 16));
}

Score::~Score()
{
}

void Score::increaseScore()
{
	score += 10;
	setPlainText(QString("Score = ") + QString::number(score));
}
