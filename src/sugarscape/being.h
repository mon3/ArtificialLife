#ifndef BEING_H
#define BEING_H

#include <QObject>
#include "src/shared/parametersset.h"
#include "src/view/visitor.h"
#include <memory>


/*!
 * \defgroup sugarscape Sugarscape logic module
 * \brief defines logic and behaviour elements typical for artificial societies
 *
*/



/*!
 * \ingroup sugarscape
 * \brief The Being class - base class for all creatures on board
 *
 *
 * \details Stores information about health & logic coordinates of the creature; Cannot
 *  be instatiated
 */
class Being : public QObject
{
    Q_OBJECT
public:
    Being(int _logX, int _logY);
    int getHitPoints() const;
    void setHitPoints(int value);

    int getLogX() const;
    void setLogX(int value);

    int getLogY() const;
    void setLogY(int value);


    /*!
     * \brief action - behavior logic function
     *
     * \details According to current state, being performs actions to maintain an optimal state
     */
    virtual void action() = 0;

    virtual  int type() const = 0 ;

    /*!
     * \brief accept - visitor pattern implementation
     *
     * \details Accept visitor, which will perform actions, according to it's type
     */
    virtual void accept(Visitor*) = 0;
    bool getIsDead() const;
    void setIsDead();
private:

    /// to allow view to decide, whether to remove this being
    bool isDead;

    int logX;
    int logY;
    int hitPoints;
};

#endif // BEING_H
