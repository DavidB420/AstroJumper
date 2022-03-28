/*--------------------------------------------------------------------------------
* David Badiei, Nathan Vuong
* 06/13/2022
* ICS4U1
* Player.cpp
* Creates Player object, handles key press and release events, and handles player
* physics and platform hit detection.
*-------------------------------------------------------------------------------*/

#include "Player.h"
#include "Game.h"

extern Game* game; //Access game object from player object

/**
* Creates Player object, initializes most variables to their default positions, and saves the game difficulty
* @param difficulty The current diffiulty level
* @param parent Inherits the QGraphicsPixmapItem class
*/
Player::Player(int difficulty, QGraphicsPixmapItem* parent)
{
	//Set variables to default positions
	xPos = 350;
	yPos = 500;
	angle = -1;
	currentDifficulty = difficulty;
	prevAngle = angle;
	firstJump = false;
	playerPlatform = NULL;
	deathSfxPlayed = false;

	//Make player object be visible above all other objects
	setZValue(69);

	//Set default player sprite from resource file
	setPixmap(QPixmap(":/images/Images/playerLeft.png"));

	//Set default position
	setPos(xPos, yPos);

	//Make player object the focus
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFocus();

	//Create timer that will run the physics function every 10 miliseconds
	timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(playerPhysics()));
	timer->start(10);

	//Jump sound
	jumpSfx = new QMediaPlayer(this);
	jumpSfx->setMedia(QUrl("qrc:/sounds/Sounds/jump.mp3"));

	//Death sound
	deathSfx = new QMediaPlayer(this);
	deathSfx->setMedia(QUrl("qrc:/sounds/Sounds/deathtest.mp3"));

	//Walking sound
	walkSfx = new QMediaPlayer(this);
	walkSfx->setMedia(QUrl("qrc:/sounds/Sounds/walking.mp3"));

}

/**
* Handles all key press events
* @param event Contains the key event 
*/
void Player::keyPressEvent(QKeyEvent* event)
{
	//Determine which key was pressed
	switch (event->key())
	{
	case Qt::Key_Up:
		angle = 90; //Set angle to 90 degrees (Vertically up)
		prevAngle = angle; //Set the previous angle to the current angle
		jumpSfx->play(); //Play jump sfx
		break;
	case Qt::Key_Left:
		if (angle == -1) //If the angle is equal to -1 (Player is on a surface) play the walking sfx
		{
			walkSfx->play();
		}
		if (xPos >= 0) //If the player isnt on the very left of the screen, move the player left
		{
			xPos -= 15; //Move 15 pixels to the left
			#ifdef MACOS //Mac needs another 15 pixels to make it playable
				xPos -= 15;
			#endif
			angle = prevAngle; //Set angle equal to previous angle
			
			//Set new position
			setPos(xPos, yPos);
		}
		setPixmap(QPixmap(":/images/Images/playerMovingLeft.png")); //Set player sprite to the left facing moving sprite
		break;
	case Qt::Key_Right:
		if (angle == -1) //If the angle is equal to -1 (Player is on a surface) play the walking sfx
		{
			walkSfx->play();
		}
		if (xPos <= 700) //If the player isnt on the very right of the screen, move the player left
		{
			xPos += 15; //Move 15 pixels to the right
			#ifdef MACOS //Mac needs another 15 pixels to make it playable
				xPos += 15;
			#endif
			angle = prevAngle; //Set angle equal to previous angle

			//Set new position
			setPos(xPos, yPos);
		}
		setPixmap(QPixmap(":/images/Images/playerMovingRight.png")); //Set player sprite to the right facing moving sprite
		break;
	}
}

/**
* Handles all key release events
* @param event Contains the key event
*/
void Player::keyReleaseEvent(QKeyEvent* event)
{
	//Determine which key has been released
	switch (event->key())
	{
	case Qt::Key_Left:
		setPixmap(QPixmap(":/images/Images/playerLeft.png")); //Set player sprite to left facing standing sprite
		break;
	case Qt::Key_Right:
		setPixmap(QPixmap(":/images/Images/playerRight.png")); //Set player sprite to right facing standing sprite
		break;
	}
}

/**
* Handles all physics (gravity) and platform hit detection
*/
int Player::playerPhysics()
{
	//If the player is at the bottom of the screen or above, and the angle isn't -1 (null value that causes physics function to do nothing), continue
	if (yPos <= 500 && angle != -1)
	{
		//Determine delta y using projectile motion equation (Mac has a slightly lower acceleration due to gravity compared to Windows and Linux)
		#ifdef WINDOWS
			dy = (VELOCITY * sin(angle * PI / 180) * time + 0.5 * (-9.8) * (time) * (time));
		#endif
		#ifdef LINUX
			dy = (VELOCITY * sin(angle * PI / 180) * time + 0.5 * (-9.8) * (time) * (time));
		#endif
		#ifdef MACOS
			dy = (VELOCITY * sin(angle * PI / 180) * time + 0.5 * (-9.7) * (time) * (time));
		#endif

		//Update y position with delta y
		yPos -= dy;

		//Only check for collisions if the sign of dy is negative (player is going down)
		if (dy < 0)
		{
			//Create and parse through list of colliding items
			QList<QGraphicsItem*> collidingitems = collidingItems();
			for (int i = 0, n = collidingitems.size(); i < n; i++)
			{
				//Continue if the player collided with a platform
				if (typeid(*(collidingitems[i])) == typeid(Platform))
				{
					/*Calculate difference between the y position of the playerand the y position of the colliding item,
					so we know if the player actually jumped on the platform*/
					int diffPlayerPlatform = yPos - collidingitems[i]->y();

					//If this value is less than or equal to -79 (found using empirical testing to be the best value), continue 
					if (diffPlayerPlatform <= -79)
					{
						//If this isn't the first jump, continue
						if (firstJump)
						{
							//Make sure this is a new platform the player has jumped on
							if (playerPlatform != collidingitems[i])
							{
								//Remove platform from game scene
								scene()->removeItem(game->platform[0]);

								//Set first game platform to null
								game->platform[0] = NULL;

								//Shift remaining platforms down
								for (int currentPlatform = 0; currentPlatform < 4; currentPlatform++)
								{
									game->platform[currentPlatform] = game->platform[currentPlatform + 1];

									game->platform[currentPlatform]->posY += 100;
									game->platform[currentPlatform]->placePlatform();
								}

								
								//Generate new platform at the top
								game->generateGamePlatforms(4, 5, 60);

								//Save a copy of the platform the player has jumped on
								playerPlatform = collidingitems[i];

								//Increment score
								game->score->increaseScore();

								//If the difficulty is equal to Difficult or above, begin the break procedure
								if (currentDifficulty >= 2)
								{
									game->platform[0]->startBreakProcedure();
								}
							}

						}

						//If this is the first jump, continue
						if (!firstJump)
						{
							//Save a copy of the platform the player has jumped on
							playerPlatform = collidingitems[i];

							//Increment score
							game->score->increaseScore();
							
							//If the difficulty is equal to Difficult or above, begin the break procedure
							if (currentDifficulty >= 2)
							{
								game->platform[0]->startBreakProcedure();
							}
						}
						
						//If the player lands on the same platform they were on before and platform is broken, continue
						if (playerPlatform == collidingitems[i] && game->platform[0]->isBroken())
						{
							angle = 0; //Set angle to zero so it falls
							prevAngle = angle; //Set previous angle to angle
						}
						else //Otherwise have the player stay on the platform
						{
							angle = -1; //Set angle to null
							prevAngle = 0; //Set previous angle to 0
							yPos = collidingitems[i]->y() - 100; //Have the player be directly on top of the platform
							time = 0; //Reset time counter
							dy = 0; //Reset delta y
						}

						
						//Update first jump
						firstJump = true;


					}
				}
			}
		}

		//Update time counter
		time += 0.01;

		//Update player position
		setPos(xPos, yPos);
	}

	//If the player has fallen off a platform, continue
	if (yPos > 500 && firstJump == true)
	{
		//If the death sfx isn't playing, continue
		if (deathSfx->state() == QMediaPlayer::StoppedState)
		{
			if (!deathSfxPlayed)
			{
				deathSfx->play();
			}
			else
			{
				scene()->removeItem(this);
				delete this;
				game->loadHighScore();
			}
		}
		else if (deathSfx->state() == QMediaPlayer::PlayingState)
		{
			deathSfxPlayed = true;
		}
		return NULL;
	}

	//If the player has landed on the ground but hasn't fallen from a platform, continue
	if (yPos > 500)
	{
		angle = -1; //Set the angle to null
		prevAngle = angle; //Set the previous angle to null
		yPos = 500; //Set the player's y position to the bottom of the screen
		time = 0; //Reset time counter
		dy = 0; //Reset delta y
	}

	//If the platform has broken and the player is still on it, have them fall
	if (game->platform[0]->isBroken() && angle == -1 && dy == 0)
	{
		angle = 0; //Set angle to zero so they fall
		prevAngle = angle; //Set previous angle to angle
	}

	return NULL; //End the function by returning NULL
}
