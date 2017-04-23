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
<<<<<<< HEAD
    void setHitPoints(int value);    
=======
    void setHitPoints(int value);
>>>>>>> multi_dev

private:
    int logX;
    int logY;
    int hitPoints;
};

#endif // CREATURE_H
