#include "beingitem.h"

BeingItem::BeingItem(Being *b) :
    QGraphicsRectItem(0, 0, ParametersSet::BEING_WIDTH, ParametersSet::BEING_WIDTH)
{
    being = std::make_unique<Being>(b);
}

void BeingItem::updateBeing()
{
    being->update();
}

void BeingItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit callWindow(being.get());
}

void BeingItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    this->painter = painter;
    visit(being.get());
    painter = nullptr;
}


void BeingItem::visit(Plant *)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(this->rect());
}

void BeingItem::visit(Predator *)
{
    painter->setBrush(Qt::red);
    painter->drawRect(this->rect());
}

void BeingItem::visit(Herbivorous *)
{
    painter->setPen(Qt::blue);
    painter->drawRect(this->rect());
}
