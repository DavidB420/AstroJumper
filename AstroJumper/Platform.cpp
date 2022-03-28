#include "Platform.h"

Platform::Platform(QGraphicsRectItem* parent)
{
	//setRect(QRectF(posX, posY, 150, 50));
	platformMoveTimer = new QTimer();
	//connect(platformMoveTimer, SIGNAL(timeout()), this, SLOT(moveDown()));
	//platformMoveTimer->start(100);
}

Platform::~Platform()
{
}

void Platform::placePlatform()
{
	setRect(QRectF(posX, posY, 150, 50));
}

void Platform::moveDown()
{
	posY += 5;
	setRect(QRectF(posX, posY, 150, 50));
}