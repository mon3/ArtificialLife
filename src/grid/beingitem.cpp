#include "beingitem.h"

Being* BeingItem::getBeing() const
{
    return being.get();
}

BeingItem::BeingItem(Being*&& b) :
    QGraphicsRectItem(0, 0, ParametersSet::BEING_WIDTH, ParametersSet::BEING_WIDTH), Visitor()
{
    being = std::unique_ptr<Being>(b);
}

void BeingItem::updateBeing()
{
    being->action();
    if(being->getIsDead()) {
        being.get()->accept(Board::getInstance());
        this->scene()->removeItem(this);
        delete this;
        return;
    }
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
    painter->setPen(Qt::green);
    painter->drawRect(this->rect());
}
