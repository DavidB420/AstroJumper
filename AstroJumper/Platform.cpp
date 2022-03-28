#include "Platform.h"

Platform::Platform(QGraphicsPixmapItem* parent)
{
	setPixmap(QPixmap(":/images/Images/meteor.png"));
	
	broken = false;
}

Platform::~Platform()
{
}

void Platform::placePlatform()
{
	setPos(posX, posY);
}

void Platform::startBreakProcedure()
{
	setPixmap(QPixmap(":/images/Images/meteorCracked.png"));
	QTimer::singleShot(5000, this, SLOT(breakPlatform()));
}

bool Platform::isBroken()
{
	return broken;
}

void Platform::breakPlatform()
{
	broken = true;
	setPixmap(QPixmap(":/images/Images/meteorBroken.png"));
}