#ifndef VISITOR_H
#define VISITOR_H

//#include "src/sugarscape/herbivorous.h"
//#include "src/sugarscape/plant.h"
//#include "src/sugarscape/predator.h"
class Plant;
class Predator;
class Herbivorous;
class Visitor
{
public:
    Visitor() { }
    virtual void visit(Plant*) = 0;
    virtual void visit(Predator*) = 0;
    virtual void visit(Herbivorous*) = 0;
};

#endif // VISITOR_H
