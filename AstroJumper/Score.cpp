#include "Score.h"
#include <QFont>

Score::Score(int difficulty, QGraphicsTextItem* parent)
{
	score = 0;
	currentDifficulty = difficulty;

	setPlainText(QString("Score = ") + QString::number(score));
	setDefaultTextColor(Qt::white);
	setFont(QFont("Arial", 16));
}

Score::~Score()
{
}

void Score::increaseScore()
{
	switch (currentDifficulty)
	{
	case 0:
		score += 1;
		break;
	case 1:
		score += 5;
		break;
	case 2:
		score += 10;
		break;
	}
	setPlainText(QString("Score = ") + QString::number(score));
}
