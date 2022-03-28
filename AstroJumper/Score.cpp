/*--------------------------------------------------------------------------------
* David Badiei
* 06/13/2022
* ICS4U1
* Score.cpp
* Creates Score object, displays and stores player score
*-------------------------------------------------------------------------------*/

#include "Score.h"
#include <QFont>

/**
* Initializes the score object, sets player score to zero, and stores current game difficulty
* @param difficulty The current diffiulty level
* @param parent Inherits the QGraphicsTextItem class
*/
Score::Score(int difficulty, QGraphicsTextItem* parent)
{
	//Set score to zero
	score = 0;

	//Save current difficulty
	currentDifficulty = difficulty;

	//Display score with its default value
	setPlainText(QString("Score = ") + QString::number(score));

	//Set font size and color
	setDefaultTextColor(Qt::white);
	setFont(QFont("Arial", 16));
}

/**
* Increments the score by 10 (Nightmare), 5 (Difficult), and 1 (Easy), and displays it to the user
*/
void Score::increaseScore()
{
	//Determine which difficulty the user is playing with, and add the number of points accordingly
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

	//Display new score
	setPlainText(QString("Score = ") + QString::number(score));
}
