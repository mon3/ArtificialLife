#ifndef BEING_H
#define BEING_H

#include <QObject>
#include <QPainter>
#include <QGraphicsRectItem>
#include "parametersset.h"
class Being : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:

    Being(int _logX, int _logY);
    int mapCoordinates(int, int);
    int getHitPoints() const;
    static int sceneSize; // consider
    void setHitPoints(int value);

    //qt for static cast
    int type() const  { return 213; }
    int getLogX() const;
    void setLogX(int value);

    int getLogY() const;
    void setLogY(int value);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    virtual int getPenColor() const = 0;
    int logX;
    int logY;
    int hitPoints;
};

#endif // BEING_H
