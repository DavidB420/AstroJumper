/*--------------------------------------------------------------------------------
* David Badiei
* 06/13/2022
* ICS4U1
* Platform.h
* Header (definition file) for Platform object
*-------------------------------------------------------------------------------*/

#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QEvent>

class Platform : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	Platform(QGraphicsPixmapItem* parent = 0);
	void placePlatform();
	int posX = 0, posY = 0;
	bool isBroken();
	void startBreakProcedure();
private:
	bool broken;
private slots:
	void breakPlatform();
};
#endif