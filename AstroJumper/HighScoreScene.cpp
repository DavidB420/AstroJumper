/*--------------------------------------------------------------------------------
* David Badiei
* 06/13/2022
* ICS4U1
* HighScoreScene.cpp
* Creates high score scene with all of its children: the top five table and the 
* player score with either the name entry prompt and/or play again button.
*-------------------------------------------------------------------------------*/

#include "HighScoreScene.h"
#include "Game.h"

extern Game* game; //Access game object from high score scene object

/**
* Initialize high score scene object with the scene containing all the children needed and gets the current player names and scores from HIGHSCORE.LST.
* @param score The current score
* @param parent Inherits the QGraphicsScene class
*/
HighScoreScene::HighScoreScene(int score, QGraphicsScene *parent)
{
	//Save score
	currentScore = score;

	//Set up scene with its resolution and background image
	setSceneRect(0, 0, 800, 600);
	setBackgroundBrush(QBrush(QImage(":/images/Images/highScoreBg.png")));

	//Display top 5 player's names
	for (int i = 0; i < 5; i++)
	{
		top5PlayersScore[0][i] = new QGraphicsTextItem(); //Create text item object
		top5PlayersScore[0][i]->setPlainText(returnPlayerNameOrScore(i,true)); //Get value from HIGHSCORE.LST
		top5PlayersScore[0][i]->setPos(100, 100 + (75 * i)); //Set position (make it come out as a list)
		top5PlayersScore[0][i]->setDefaultTextColor(Qt::white); //Set text color
		top5PlayersScore[0][i]->setFont(QFont("Arial", 24)); //Set font
		addItem(top5PlayersScore[0][i]); //Add item to scene
	}

	//Display top 5 player's scores
	for (int i = 0; i < 5; i++)
	{
		top5PlayersScore[1][i] = new QGraphicsTextItem(); //Create text item object
		top5PlayersScore[1][i]->setPlainText(returnPlayerNameOrScore(i,false)); //Get value from HIGHSCORE.LST
		top5PlayersScore[1][i]->setPos(650, 100 + (75 * i)); //Set position (make it come out as a list)
		top5PlayersScore[1][i]->setDefaultTextColor(Qt::white); //Set text color
		top5PlayersScore[1][i]->setFont(QFont("Arial", 24)); //Set font
		addItem(top5PlayersScore[1][i]); //Add item to scene
	}
	
	//If the player maanaged to reach the top 5, continue
	if (getPosInFile(score) < 5)
	{
		//Create and add name entry prompt
		nameEntry = new QLineEdit();
		nameEntry->resize(350, 20);
		nameEntry->move(100, 500);
		nameEntryProxy = addWidget(nameEntry);

		//Create and add submit button
		submitNameButton = new QPushButton();
		submitNameButton->setText("Submit Name (Max 10 Chars)");
		submitNameButton->move(500, 495);
		submitNameButtonProxy = addWidget(submitNameButton);

		//Wait for user pressed enter or pressed submit, then save the name and score
		connect(submitNameButton, SIGNAL(clicked()), this, SLOT(submitName()));
		connect(nameEntry, SIGNAL(returnPressed()), this, SLOT(submitName()));
	}
	else //Otherwise just give them the play again button
	{
		createPlayAgainButton();
	}

	//Display the user's score at the bottom of the screen
	QGraphicsTextItem* scoreDisplay = new QGraphicsTextItem();
	scoreDisplay->setPlainText(QString("Score: ") + QString::number(score));
	scoreDisplay->setPos(300, 550);
	scoreDisplay->setDefaultTextColor(Qt::white);
	scoreDisplay->setFont(QFont("Arial", 24));
	addItem(scoreDisplay);
}

/**
* Returns specified score or name
* @param index The line where the data is located 
* @param getName Specify if the name or score should be returned
* @return The specified score or name
*/
QString HighScoreScene::returnPlayerNameOrScore(int index, bool getName)
{
	//Declare variables
	QString buf;
	ifstream scoreFile;
	loadHighScoreFile(scoreFile);
	string line;
	
	//If HIGHSCORE.LST managed to load in, continue
	if (scoreFile.is_open())
	{
		//Parse through file until we reach specified line
		for (int i = 0; i <= index; i++)
		{
			getline(scoreFile, line);
		}

		//If the line isn't blank, continue
		if (line.length() != 0)
		{
			//If the name is required, continue
			if (getName)
			{
				//Save the name portion of the line into a buffer
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
			else //If the score is required, continue
			{
				//Save the score portion of the line into a buffer
				for (int i = line.find((char)(0xff)) + 1; i < line.length(); i++)
				{
					buf.append(line.at(i));
				}
			}
		}
		else //Otherwise return blanks (4 blanks for name, 2 blanks for score)
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
	else //Otherwise return blanks (4 blanks for name, 2 blanks for score)
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

	//Return saved name or score
	return buf;
}

/**
* Returns what line in HIGHSCORE.LST the new score should be stored
* @param score The score the user managed to get
* @return The line where the score should be saved
*/
int HighScoreScene::getPosInFile(int score)
{
	//Declare variables
	ifstream scoreFile;
	loadHighScoreFile(scoreFile);
	string line, buf;
	int currentLine = 0;

	//If the file can be opened, continue
	if (scoreFile.is_open())
	{
		//Cycle through all lines
		while (currentLine < getNumOfLines())
		{
			//Get the score from the current line
			getline(scoreFile, line);
			buf.append(&line.at(line.find((char)(0xff)) + 1));

			//If the player's score is higher than the score on the current line, continue
			if (score > stoi(buf))
			{
				return currentLine;
			}

			//Otherwise cycle to the next line and clear the buffer
			currentLine++;
			buf = "";
		}

	}

	//Return 0 as the default value
	return currentLine;
}

/**
* Returns number of lines in HIGHSCORE.LST
* @return Number of lines in HIGHSCORE.LST
*/
int HighScoreScene::getNumOfLines()
{
	//Declare variables
	ifstream scoreFile;
	loadHighScoreFile(scoreFile);
	string line;
	int lines = 0;

	//Keep running until we reach reach the end of the file
	while (!scoreFile.eof())
	{
		getline(scoreFile, line); //Load in a new line
		lines++; //Increment line counter
	}

	return lines-1; //last line is eof
}

/**
* Creates a play again button that will relaunch the game when clicked.
*/
void HighScoreScene::createPlayAgainButton()
{
	//Create and add the play again button
	QPushButton* playAgain = new QPushButton();
	playAgain->setText("Play Again!");
	playAgain->move(348, 495);
	QGraphicsProxyWidget* playAgainProxy = addWidget(playAgain);

	//Wait for the user to press the play again button, then relaunch the game
	connect(playAgain, SIGNAL(clicked()), this, SLOT(relaunchGame()));
}

/**
* Loads HIGHSCORE.LST into input stream
* @param scoreFile Pointer to input stream
*/
void HighScoreScene::loadHighScoreFile(ifstream &scoreFile)
{
	//Generate file path to HIGHSCORE.LST (Depends if you are running a Windows-based system or UNIX-based system such as Linux or Mac OS)
	#ifdef WINDOWS
		char userProfilePath[0xffff];
		ExpandEnvironmentStringsA("%userprofile%", userProfilePath, 0xffff);
		strcat(userProfilePath, "\\HIGHSCORE.LST");
	#endif
	#ifdef LINUX
		string userProfilePath = getenv("HOME");
		userProfilePath.append("/HIGHSCORE.LST");
	#endif
	#ifdef MACOS
		string userProfilePath = getenv("HOME");
		userProfilePath.append("/HIGHSCORE.LST");
	#endif

	//Load HIGHSCORE.LST
	scoreFile.open(userProfilePath);
}

/**
* Calls the game class’s launch game function. 
*/
void HighScoreScene::relaunchGame()
{
	//Launches game with specified difficulty
	game->launchGame(game->currentDifficulty);
}

/**
* Updates HIGHSCORE.LST with new score and name.
*/
void HighScoreScene::submitName()
{
	//If the value in the name entry meets the requirements, continue
	if (nameEntry->text().length() <= 10 && nameEntry->text().length() > 0)
	{
		//Declare variables
		ifstream scoreFile;
		loadHighScoreFile(scoreFile);
		ofstream writeFile;
		vector <string> buf; //A vector is a type of array in C++ that has an dynamic size
		string bufLine;

		//Generate file path to HIGHSCORE.LST (Depends if you are running a Windows-based system or UNIX-based system such as Linux or Mac OS)
		#ifdef WINDOWS
		    char userProfilePath[0xffff];
		    ExpandEnvironmentStringsA("%userprofile%", userProfilePath, 0xffff);
		    strcat(userProfilePath, "\\HIGHSCORE.LST");
		#endif
		#ifdef LINUX
		    string userProfilePath = getenv("HOME");
		    userProfilePath.append("/HIGHSCORE.LST");
		#endif
		#ifdef MACOS
		    string userProfilePath = getenv("HOME");
		    userProfilePath.append("/HIGHSCORE.LST");
		#endif

		//If the score file managed to open, continue
		if (scoreFile.is_open())
		{
			//Parse through entire file and add a new line at the end 
			while (!scoreFile.eof())
			{
				getline(scoreFile, bufLine);
				buf.push_back(bufLine + "\n");
			}
		}
		else //Otherwise, prepare the buffer for the creation of a new HIGHSCORE.LST
		{
			buf.push_back("\n");
		}
		
		//Insert new line with the name and score (0xff will seperate the two values)
		buf.insert(buf.begin() + getPosInFile(currentScore), nameEntry->text().toStdString() + (char)(0xff) + to_string(currentScore) + "\n");
		
		//Load in HIGHSCORE.LST into the output stream
		writeFile.open(userProfilePath, ofstream::trunc);

		//Parse through the buffer and save the top 5 in the buffer
		for (int i = 0; i < buf.size() - 1; i++)
		{
			writeFile << buf.at(i);
			if (i >= 4) //only want to save top 5
			{
				break;
			}
		}

		//Close both the input and output stream
		scoreFile.close();
		writeFile.close();

		//Update name and score display with updated HIGHSCORE.LST
		for (int i = 0; i < 5; i++)
		{
			top5PlayersScore[0][i]->setPlainText(returnPlayerNameOrScore(i, true));
			top5PlayersScore[1][i]->setPlainText(returnPlayerNameOrScore(i, false));
		}

		//Delete the name entry prompt and submit name button after this function has finished executing
		nameEntry->deleteLater();
		submitNameButton->deleteLater();

		//Display the play again button
		createPlayAgainButton();
	}
	else if (nameEntry->text().length() == 0) //Display error message if the user didn't enter anything into the score box
	{
		QMessageBox* mBox = new QMessageBox();
		mBox->setText("Enter name!");
		mBox->setIcon(QMessageBox::Critical);
		mBox->setWindowTitle("Error");
		mBox->show();
	}
	else //Display error message if the user entered a name more than 10 characters
	{
		QMessageBox* mBox = new QMessageBox();
		mBox->setText("Max 10 Chars!");
		mBox->setIcon(QMessageBox::Critical);
		mBox->setWindowTitle("Error");
		mBox->show();
	}
}
