/*--------------------------------------------------------------------------------
* David Badiei, Nathan Vuong
* 06/13/2022
* ICS4U1
* Projectile.cpp
* Creates a projectile that moves down the screen
*-------------------------------------------------------------------------------*/

#include "Projectile.h"
#include "Game.h"

extern Game* game; //Access game object from projectile object

/**
* Creates the projectile, initializes both sound effects, and plays the gun shot sound effect
* @param parent Inherits the QGraphicsPixmapItem class
*/
Projectile::Projectile(QGraphicsPixmapItem* parent)
{
	//Set hit player checker to false
	hitPlayer = false;
	
	//Set projectile sprite
	setPixmap(QPixmap(":/images/Images/projectile.png"));

	//Have the projectile be visible above the player
	setZValue(70);

	//Move the projectile down 10 pixels every 50 miliseconds
	QTimer* timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(move()));
	timer->start(50);
	
	//gun sound
	gunSfx = new QMediaPlayer(this);
	gunSfx->setMedia(QUrl("qrc:/sounds/Sounds/gunShot.mp3"));
	gunSfx->play();

	//Death sound
	deathSfx = new QMediaPlayer(this);
	deathSfx->setMedia(QUrl("qrc:/sounds/Sounds/deathtest.mp3"));
	
}

/**
* Moves the projectile down 10 pixels and provides hit detection with the player.
* @return NULL
*/
int Projectile::move()
{
	//Move the projectile down 10 pixels
	setPos(x(), y() + 10);

	//If the projectile reaches the bottom, remove it and exit out of the function
	if (y() >= 600)
	{
		//If the hit player checker is set to false, remove it from the scene
		if (!hitPlayer)
		{
			scene()->removeItem(this);
		}

		//Delete projectile object
		delete this;

		//End the function by returning NULL
		return NULL;
	}

	//Create and parse through list of colliding items
	QList<QGraphicsItem*> collidingitems = collidingItems();
	for (int i = 0, n = collidingitems.size(); i < n; i++)
	{
		//Continue if the projectile collided with the player
		if (typeid(*(collidingitems[i])) == typeid(Player))
		{
			//If the death sfx isn't playing, continue
			if (deathSfx->state() == QMediaPlayer::StoppedState)
			{
				//Delete player object
				delete collidingitems[i];

				//Remove projectile object from scene
				scene()->removeItem(this);

				//Play death sfx
				deathSfx->play();

				//Set hit player checker to true
				hitPlayer = true;

				//Begin loading in the high score scene
				game->loadHighScore();
			}
			
			return NULL; //End the function by returning NULL
		}
	}

	return NULL; //End the function by returning NULL
	
}