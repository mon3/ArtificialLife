#include "beingitem.h"

BeingItem::BeingItem(Being *b) :
    QGraphicsRectItem(0, 0, ParametersSet::BEING_WIDTH, ParametersSet::BEING_WIDTH)
{
    being = std::make_unique<Being>(b);
}

void BeingItem::updateBeing()
{
    being->action();
    const int WIDTH = ParameterSet::SCENE_WIDTH;
    const int OFFSET = ParametersSet::BEING_WIDTH >> 1;
    this->setPos((being->getLogX() * WIDTH) / gridSize + OFFSET,
              (being->getLogY() * WIDTH) / gridSize + OFFSET);
}

void BeingItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit callWindow(being.get());
}

void BeingItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    this->painter = painter;
    visit(being.get());
    this->painter = nullptr;
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
