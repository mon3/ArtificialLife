#include "animal.h"


void Animal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    painter->setPen(Qt::blue);
    qDebug() << "here " << this->pos() << this->rect();
    painter->drawRect(this->rect());
}

void Animal::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "Pressed!";
}

//Animal::hunt(Being & being)
//{

//}
