#include "beingitem.h"

BeingItem::BeingItem(std::unique_ptr<Being>& b) :
    QGraphicsRectItem(0, 0, ParametersSet::BEING_WIDTH, ParametersSet::BEING_WIDTH), Visitor()
{
    being = std::move(b);
}

void BeingItem::updateBeing()
{
    being->action();

    const int WIDTH = ParametersSet::SCENE_WIDTH;
    const int OFFSET = ParametersSet::BEING_WIDTH >> 1;
    const int gridSize = ParametersSet::getInstance()->getGridSize();
    this->setPos((being->getLogX() * WIDTH) / gridSize + OFFSET,
              (being->getLogY() * WIDTH) / gridSize + OFFSET);
}

void BeingItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit callWindow(being.get());
}

void BeingItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * s, QWidget * w)
{
    Q_UNUSED(s); Q_UNUSED(w);
    this->painter = painter;
    being->accept(this);
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
