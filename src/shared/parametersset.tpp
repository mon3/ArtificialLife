#ifndef PARAMETERSSET_TPP
#define PARAMETERSSET_TPP

template<typename T>
std::vector<T> ParametersSet::getAdjacentBeings(int logX, int logY, const int reach) const
{
    std::vector<T> result;
//    int logX = a->getLogX(), logY = a->getLogY();
    int checkX, checkY;
    for(int i = 1; i <= reach; ++i)
        for(int j = 0; j < 4; ++j) {
            checkX = logX + i * getRowMod(j);
            checkY = logY + i * getColMod(j);
            if(checkCoordinate(checkX, checkY)
                    && animalsOnBoard[checkX][checkY] != nullptr) {
                T being =  qobject_cast<T>(animalsOnBoard[checkX][checkY]);
                if(being != 0)
                    result.push_back(being);
            }
        }
    return result;
}


#endif // PARAMETERSSET_TPP
