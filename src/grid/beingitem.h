#ifndef BEINGITEM_H
#define BEINGITEM_H

#include <memory>

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPainter>
#include "src/shared/board.h"
#include "src/sugarscape/being.h"
#include "src/shared/parametersset.h"

/*!
 * \brief The BeingItem class Responsible for drawing
 */
class BeingItem : public QObject, public QGraphicsRectItem, public Visitor
{
    Q_OBJECT
private:
    std::unique_ptr<Being> being;
    QPainter* painter = nullptr;
    static int magic_offset;
public:
    BeingItem(Being*&& b);

public slots:
    void updateBeing();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
signals:
    void callWindow(Being*);
    // Visitor interface
public:
    /*!
     * \brief visit Visitor pattern implementation; responsible for drawing plant
     * \param p
     */
    void visit(Plant *p) override;
    /*!
     * \brief visit Visitor pattern implementation; responsible for drawing predator
     * \param p
     */
    void visit(Predator *p) override;
    /*!
     * \brief visit Visitor pattern implementation; responsible for drawing Herbivorous
     * \param p
     */
    void visit(Herbivorous *p) override;

    /*!
     * \brief getBeing Return being pointer stored within class
     * \return Model being pointer
     */
    Being* getBeing() const;
};

#endif // BEINGITEM_H
