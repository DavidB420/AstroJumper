#include "HighScoreScene.h"
#include "Game.h"

extern Game* game;

using namespace std;

HighScoreScene::HighScoreScene(int score, QGraphicsScene *parent)
{
	currentScore = score;

	setSceneRect(0, 0, 800, 600);
	setBackgroundBrush(QBrush(QImage(":/images/Images/highScoreBg.png")));

	for (int i = 0; i < 5; i++)
	{
		top5Players[i] = new QGraphicsTextItem();
		top5Players[i]->setPlainText(returnPlayerNameOrScore(i,true));
		top5Players[i]->setPos(100, 100 + (75 * i));
		top5Players[i]->setDefaultTextColor(Qt::white);
		top5Players[i]->setFont(QFont("Arial", 24));
		addItem(top5Players[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		top5PlayersScore[i] = new QGraphicsTextItem();
		top5PlayersScore[i]->setPlainText(returnPlayerNameOrScore(i,false));
		top5PlayersScore[i]->setPos(650, 100 + (75 * i));
		top5PlayersScore[i]->setDefaultTextColor(Qt::white);
		top5PlayersScore[i]->setFont(QFont("Arial", 24));
		addItem(top5PlayersScore[i]);
	}
	
	if (getPosInFile(score) < 5)
	{
		nameEntry = new QLineEdit();
		nameEntry->resize(350, 20);
		nameEntry->move(100, 500);

		nameEntryProxy = addWidget(nameEntry);

		submitNameButton = new QPushButton();
		submitNameButton->setText("Submit Name (Max 10 Chars)");
		submitNameButton->move(500, 495);

		submitNameButtonProxy = addWidget(submitNameButton);

		connect(submitNameButton, SIGNAL(clicked()), this, SLOT(submitName()));
		connect(nameEntry, SIGNAL(returnPressed()), this, SLOT(submitName()));
	}
	else
	{
		createPlayAgainButton();
	}

	QGraphicsTextItem* scoreDisplay = new QGraphicsTextItem();
	scoreDisplay->setPlainText(QString("Score: ") + QString::number(score));
	scoreDisplay->setPos(300, 550);
	scoreDisplay->setDefaultTextColor(Qt::white);
	scoreDisplay->setFont(QFont("Arial", 24));
	addItem(scoreDisplay);
}

HighScoreScene::~HighScoreScene()
{
}

QString HighScoreScene::returnPlayerNameOrScore(int index, bool getName)
{
	QString buf;
	ifstream scoreFile;
	string line;

	char userProfilePath[0xffff];
	ExpandEnvironmentStringsA("%userprofile%", userProfilePath, 0xffff);
	strcat(userProfilePath, "\\HIGHSCORE.LST");
	scoreFile.open(userProfilePath);

	if (scoreFile.is_open())
	{
		for (int i = 0; i <= index; i++)
		{
			getline(scoreFile, line);
		}

		if (line.length() != 0)
		{
			if (getName)
			{
				for (int i = 0; i < line.length(); i++)
				{
					if (line.at(i) != -1)
					{
						buf.append(line.at(i));
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				for (int i = line.find((char)(0xff)) + 1; i < line.length(); i++)
				{
					buf.append(line.at(i));
				}
			}
		}
		else
		{
			if (getName)
			{
				return "----";
			}
			else
			{
				return "--";
			}
		}
	}
	else
	{
		if (getName)
		{
			return "----";
		}
		else
		{
			return "--";
		}
	}


	return buf;
}

int HighScoreScene::getPosInFile(int score)
{
	ifstream scoreFile;
	string line, buf;
	int currentLine = 0;

	char userProfilePath[0xffff];
	ExpandEnvironmentStringsA("%userprofile%", userProfilePath, 0xffff);
	strcat(userProfilePath, "\\HIGHSCORE.LST");
	scoreFile.open(userProfilePath);

	if (scoreFile.is_open())
	{
		while (currentLine < getNumOfLines())
		{
			getline(scoreFile, line);
			buf.append(&line.at(line.find((char)(0xff)) + 1));
			if (score > stoi(buf))
			{
				return currentLine;
			}
			currentLine++;
			buf = "";
		}

	}

	return currentLine;
}

int HighScoreScene::getNumOfLines()
{
	ifstream scoreFile;
	string line;
	int lines = 0;

	char userProfilePath[0xffff];
	ExpandEnvironmentStringsA("%userprofile%", userProfilePath, 0xffff);
	strcat(userProfilePath, "\\HIGHSCORE.LST");
	scoreFile.open(userProfilePath);

	while (!scoreFile.eof())
	{
		getline(scoreFile, line);
		lines++;
	}

	return lines-1; //last line is eof
}

void HighScoreScene::createPlayAgainButton()
{
	QPushButton* playAgain = new QPushButton();
	playAgain->setText("Play Again!");
	playAgain->move(348, 495);
	QGraphicsProxyWidget* playAgainProxy = addWidget(playAgain);
	connect(playAgain, SIGNAL(clicked()), this, SLOT(relaunchGame()));
}

void HighScoreScene::relaunchGame()
{
	game->launchGame();
}

void HighScoreScene::submitName()
{
	if (nameEntry->text().length() <= 10 && nameEntry->text().length() > 0)
	{
		ifstream scoreFile;
		ofstream writeFile;
		vector <string> buf;
		string bufLine;

		char userProfilePath[0xffff];
		ExpandEnvironmentStringsA("%userprofile%", userProfilePath, 0xffff);
		strcat(userProfilePath, "\\HIGHSCORE.LST");

		scoreFile.open(userProfilePath);
		if (scoreFile.is_open())
		{
			while (!scoreFile.eof())
			{
				getline(scoreFile, bufLine);
				buf.push_back(bufLine + "\n");
			}
		}
		else
		{
			buf.push_back("\n");
		}
		
		buf.insert(buf.begin() + getPosInFile(currentScore), nameEntry->text().toStdString() + (char)(0xff) + to_string(currentScore) + "\n");
		
		writeFile.open(userProfilePath, ofstream::trunc);

		for (int i = 0; i < buf.size() - 1; i++)
		{
			writeFile << buf.at(i);
			if (i >= 4) //only want to save top 5
			{
				break;
			}
		}

		scoreFile.close();
		writeFile.close();

		for (int i = 0; i < 5; i++)
		{
			top5Players[i]->setPlainText(returnPlayerNameOrScore(i, true));
			top5PlayersScore[i]->setPlainText(returnPlayerNameOrScore(i, false));
		}

		nameEntry->deleteLater();
		submitNameButton->deleteLater();

		createPlayAgainButton();
	}
	else if (nameEntry->text().length() == 0)
	{
		QMessageBox* mBox = new QMessageBox();
		mBox->setText("Enter name!");
		mBox->setIcon(QMessageBox::Critical);
		mBox->setWindowTitle("Error");
		mBox->show();
	}
	else
	{
		QMessageBox* mBox = new QMessageBox();
		mBox->setText("Max 10 Chars!");
		mBox->setIcon(QMessageBox::Critical);
		mBox->setWindowTitle("Error");
		mBox->show();
	}
}
