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
    int getHitPoints() const;
    void setHitPoints(int value);

    int getLogX() const;
    void setLogX(int value);

    int getLogY() const;
    void setLogY(int value);

    virtual void action() = 0;
    virtual  int type() const = 0 ;
public slots:
    void updateBeing();
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual Qt::GlobalColor getPenColor() const = 0;

private:

    int logX;
    int logY;
    int hitPoints;
};

#endif // BEING_H
