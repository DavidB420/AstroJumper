/*--------------------------------------------------------------------------------
* David Badiei
* 06/13/2022
* ICS4U1
* Platform.cpp
* Creates platform that the user can jump on, will break after 5 seconds if 
* Nightmare difficulty is chosen.
*-------------------------------------------------------------------------------*/

#include "Platform.h"

/**
* Initializes Platform object with the broken state being set to false
* @param parent Inherits QGraphicsPixmapItem class
*/
Platform::Platform(QGraphicsPixmapItem* parent)
{
	//Set platform sprite to the unbroken sprite
	setPixmap(QPixmap(":/images/Images/meteor.png"));
	
	//Set broken state to false
	broken = false;
}

/**
* Sets the platforms position
*/
void Platform::placePlatform()
{
	//Set the platform position using the posX and posY variables
	setPos(posX, posY);
}

/**
* Begins the break procedure by creating a timer that executes breakPlatform() after 5 seconds and makes the platform look cracked.
*/
void Platform::startBreakProcedure()
{
	//Set platform sprite to cracked sprite
	setPixmap(QPixmap(":/images/Images/meteorCracked.png"));

	//Create a single shot timer that will break the platform in 5 seconds
	QTimer::singleShot(5000, this, SLOT(breakPlatform()));
}

/**
* Returns broken state
* @return Broken state
*/
bool Platform::isBroken()
{
	//Return broken state
	return broken;
}

/**
* Makes the platform look broken and sets broken to true.
*/
void Platform::breakPlatform()
{
	//Set broken to true
	broken = true;

	//Set platform sprite to broken sprite
	setPixmap(QPixmap(":/images/Images/meteorBroken.png"));
}