#include "herbivorous.h"





void Herbivorous::hunt()
{

    //if not, l
    vector<Being*> vec = ParametersSet::getInstance()->getAdjacentHuntSubjects(this);

    auto new_end = remove_if(vec.begin(), vec.end(), [&] (Being* b) -> bool {
       return qobject_cast<Plant*>(b) == 0;
    });

    vec.erase(new_end, vec.end());


    //find most valuable plant
    Plant* p;
    int maxSugar = numeric_limits<int>::min();

    for(vector<Being*>::iterator it = vec.begin(); it != vec.end(); ++it) {
        int temp = (*it)->getHitPoints();
        if(temp > maxSugar) {
            maxSugar = temp;
            p = qobject_cast<Plant*>((*it));
        }

    }

}
