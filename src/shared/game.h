#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "parametersset.h"

class Game
{
    Q_OBJECT
private:
    Board b;

public:
    Game();

public slots:
    void updateGame();
};

#endif // GAME_H
