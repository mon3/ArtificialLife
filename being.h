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

    int getLogX() const;
    void setLogX(int value);

    int getLogY() const;
    void setLogY(int value);

    virtual void action() = 0;
    virtual  int type() const = 0 ;
    void paint(QPainter *painter);


protected:
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    virtual Qt::GlobalColor getPenColor() const = 0;

    int logX;
    int logY;
    int hitPoints;


};

#endif // BEING_H
