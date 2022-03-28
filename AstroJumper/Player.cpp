#include "Player.h"

Player::Player(QGraphicsRectItem* parent)
{
	dx = 350;
	dy = 500;
	angle = 90;
	setRect(QRectF(dx, dy, 100, 100));
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFocus();
}

Player::~Player()
{
}

void Player::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_Up:
		createTimer(90, 10);
		break;
	case Qt::Key_Left:
		if (dx >= 0)
		{
			dx -= 10;
			setRect(QRectF(dx, dy, 100, 100));
		}
		break;
	case Qt::Key_Right:
		if (dx <= 700)
		{
			dx += 10;
			setRect(QRectF(dx, dy, 100, 100));
		}
		break;
	}
}

void Player::createTimer(int theta, int speed)
{
	angle = theta;
	if (!timer)
	{
		timer = new QTimer();
		connect(timer, SIGNAL(timeout()), this, SLOT(jump()));
		timer->start(speed);
	}
}

void Player::jump()
{
	if (dy <= 500)
	{
		dy = dy - (VELOCITY * sin(angle * PI / 180) * time + 0.5 * (-9.8) * (time) * (time));
		dx = dx + VELOCITY * cos(angle * PI / 180) * time;
		time += 0.01;
		setRect(QRectF(dx, dy, 100, 100));
	}
	else
	{
		time = 0;
		dy = 500;
		timer->stop();
		timer = NULL;
	}
}
