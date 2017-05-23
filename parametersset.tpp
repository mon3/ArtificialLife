#ifndef PARAMETERSSET_TPP
#define PARAMETERSSET_TPP

template<typename T>
vector<T*> ParametersSet::getAdjacentBeings(const Animal * a) const
{
    qDebug() << "here, in temp funk!";
    vector<T*> result;
    int logX = a->getLogX(), logY = a->getLogY()
       ,eveSight = a->getEveSight();
    int checkX, checkY;
    for(int i = 1; i <= eveSight; ++i)
        for(int j = 0; j < 4; ++j) {
            checkX = logX + i * getRowMod(j);
            checkY = logY + i * getColMod(j);
            if(checkCoordinate(checkX, checkY)) {
                T* being =  qobject_cast<T*>(animalsOnBoard[checkX][checkY]);
                if(being != 0)
                    result.push_back(being);
            }
        }

    qDebug() << "outta temp!";
    return result;
}


#endif // PARAMETERSSET_TPP
