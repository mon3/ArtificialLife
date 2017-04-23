#ifndef CREATURE_H
#define CREATURE_H

#include <QObject>
#include <QGraphicsRectItem>

class Being : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:

    Being();
    int mapCoordinates(int, int);
    int getHitPoints() const;
    void setHitPoints(int value);

private:
    int logX;
    int logY;
    int hitPoints;
};

#endif // CREATURE_H
