#ifndef BEING_H
#define BEING_H

#include <QObject>
#include <QPainter>
#include <QGraphicsRectItem>

class Being : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:

    Being(int _logX, int _logY);
    int mapCoordinates(int, int);
    int getHitPoints() const;
    static int sceneSize; // consider
    void setHitPoints(int value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const  { return 213; }
    int getLogX() const;
    void setLogX(int value);

    int getLogY() const;
    void setLogY(int value);

private:
    int logX;
    int logY;
    int hitPoints;
    static const int WIDTH = 40;
};

#endif // BEING_H
