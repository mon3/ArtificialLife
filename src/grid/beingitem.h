#ifndef BEINGITEM_H
#define BEINGITEM_H

#include <memory>

#include <QObject>
#include <QGraphicsRectItem>


#include "src/sugarscape/being.h"
#include "src/shared/parametersset.h"

class BeingItem : public QGraphicsRectItem, public Visitor
{
    Q_OBJECT
private:
    std::unique_ptr<Being> being;
    QPainter* painter = nullptr;
    static int magic_offset;
public:
    BeingItem(Being* b);

public slots:
    void updateBeing();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
signals:
    void callWindow(Being*);
    // Visitor interface
public:
    void visit(Plant *p) override;
    void visit(Predator *p) override;
    void visit(Herbivorous *p) override;
};

#endif // BEINGITEM_H
