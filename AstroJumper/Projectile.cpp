#include "Projectile.h"
#include "Game.h"

extern Game* game;

Projectile::Projectile(QGraphicsPixmapItem* parent)
{
	hitPlayer = false;
	
	setPixmap(QPixmap(":/images/Images/projectile.png"));

	setZValue(70);

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

Projectile::~Projectile()
{
}

int Projectile::move()
{
	setPos(x(), y() + 10);

	if (y() >= 600)
	{
		if (!hitPlayer)
		{
			scene()->removeItem(this);
		}
		delete this;
		return NULL;
	}

	QList<QGraphicsItem*> collidingitems = collidingItems();

	for (int i = 0, n = collidingitems.size(); i < n; i++)
	{
		if (typeid(*(collidingitems[i])) == typeid(Player))
		{
			
			
			if (deathSfx->state() == QMediaPlayer::StoppedState)
			{
				delete collidingitems[i];
				scene()->removeItem(this);
				deathSfx->play();
				hitPlayer = true;
				game->loadHighScore();
			}
			
			return NULL;
		}
	}

	return NULL;
	
}