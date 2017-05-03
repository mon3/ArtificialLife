#include "animal.h"


void Animal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::red);
    painter->drawRect(this->rect());
}

//Animal::hunt(Being & being)
//{

//}
