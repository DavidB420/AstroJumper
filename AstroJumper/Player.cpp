#include "Player.h"
#include "Game.h"

extern Game* game;

Player::Player(QGraphicsPixmapItem* parent)
{
	xPos = 350;
	yPos = 500;
	angle = -1;
	prevAngle = angle;
	firstJump = false;
	playerPlatform = NULL;
	deathSfxPlayed = false;

	setZValue(69);

	setPixmap(QPixmap(":/images/Images/playerLeft.png"));

	setPos(xPos, yPos);

	setFlag(QGraphicsItem::ItemIsFocusable);
	setFocus();

	timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(playerPhysics()));
	timer->start(10);

	// Jump sound
	jumpSfx = new QMediaPlayer(this);
	jumpSfx->setMedia(QUrl("qrc:/sounds/Sounds/jump.mp3"));

	//Death sound
	deathSfx = new QMediaPlayer(this);
	deathSfx->setMedia(QUrl("qrc:/sounds/Sounds/deathtest.mp3"));

	// Walking sound
	walkSfx = new QMediaPlayer(this);
	walkSfx->setMedia(QUrl("qrc:/sounds/Sounds/walking.mp3"));

}

Player::~Player()
{
}

void Player::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_Up:
		angle = 90;
		prevAngle = angle;
		jumpSfx->play();
		break;
	case Qt::Key_Left:
		if (angle == -1)
		{
			walkSfx->play();
		}
		if (xPos >= 0)
		{
			xPos -= 15;
			angle = prevAngle;
			
			setPos(xPos, yPos);
		}
		setPixmap(QPixmap(":/images/Images/playerLeft.png"));
		break;
	case Qt::Key_Right:
		if (angle == -1)
		{
			walkSfx->play();
		}
		if (xPos <= 700)
		{
			xPos += 15;
			angle = prevAngle;
			setPos(xPos, yPos);
		}
		setPixmap(QPixmap(":/images/Images/playerRight.png"));
		break;
	}
}

int Player::playerPhysics()
{
	if (yPos <= 500 && angle != -1)
	{
		dy = (VELOCITY * sin(angle * PI / 180) * time + 0.5 * (-9.8) * (time) * (time));
		//dx = VELOCITY * cos(angle * PI / 180) * time;
		//xPos -= dx;
		yPos -= dy;

		if (dy < 0)
		{
			QList<QGraphicsItem*> collidingitems = collidingItems();
			for (int i = 0, n = collidingitems.size(); i < n; i++)
			{
				if (typeid(*(collidingitems[i])) == typeid(Platform))
				{
					int diffPlayerPlatform = yPos - collidingitems[i]->y();
					if (diffPlayerPlatform <= -79)
					{
						if (firstJump)
						{
							if (playerPlatform != collidingitems[i])
							{
								scene()->removeItem(game->platform[0]);

								game->platform[0] = NULL;

								for (int currentPlatform = 0; currentPlatform < 4; currentPlatform++)
								{
									game->platform[currentPlatform] = game->platform[currentPlatform + 1];

									game->platform[currentPlatform]->posY += 100;
									game->platform[currentPlatform]->placePlatform();
								}

								
								game->generateGamePlatforms(4, 5, 60);

								playerPlatform = collidingitems[i];

								game->score->increaseScore();

								game->platform[0]->startBreakProcedure();
							}

						}

						if (!firstJump)
						{
							playerPlatform = collidingitems[i];
							game->score->increaseScore();
							game->platform[0]->startBreakProcedure();
						}
						
						if (playerPlatform == collidingitems[i] && game->platform[0]->isBroken())
						{
							angle = 0;
							prevAngle = angle;
						}
						else
						{
							angle = -1;
							prevAngle = 0;
							yPos = collidingitems[i]->y() - 100;
							time = 0;
							dy = 0;
						}

						

						firstJump = true;


					}
				}
			}
		}

		time += 0.01;
		setPos(xPos, yPos);
	}

	if (yPos > 500 && firstJump == true)
	{
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
	if (yPos > 500)
	{
		angle = -1;
		prevAngle = angle;
		yPos = 500;
		time = 0;
		dy = 0;
	}

	if (game->platform[0]->isBroken() && angle == -1 && dy == 0)
	{
		angle = 0;
		prevAngle = angle;
	}

	return NULL;
}
