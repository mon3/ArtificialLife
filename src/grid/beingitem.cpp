#include "beingitem.h"

Being* BeingItem::getBeing() const
{
    return being.get();
}


BeingItem::BeingItem(std::shared_ptr<Being>& b) :
    QGraphicsRectItem(0, 0, ParametersSet::BEING_WIDTH, ParametersSet::BEING_WIDTH), Visitor()
{
    being = std::shared_ptr<Being>(b);
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
    this->painter_ = painter;
    being->accept(this);
}


void BeingItem::visit(Plant *)
{
    painter_->setBrush(Qt::blue);
    painter_->drawEllipse(this->rect());
}

void BeingItem::visit(Predator *)
{
    painter_->setBrush(Qt::red);
    painter_->drawRect(this->rect());
}

void BeingItem::visit(Herbivorous *)
{
    painter_->setBrush(Qt::green);
    painter_->drawRect(this->rect());
}
