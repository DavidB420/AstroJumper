#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QEvent>

class Platform : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Platform(QGraphicsRectItem* parent = 0);
	~Platform();
	void placePlatform();
	int posX = 0, posY = 0;
private:
	QTimer* platformMoveTimer;
private slots:
	void moveDown();
};
#endif