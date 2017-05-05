#include "animal.h"



void Animal::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "Pressed!";
    emit callWindow(this);

}

//Animal::hunt(Being & being)
//{

//}
