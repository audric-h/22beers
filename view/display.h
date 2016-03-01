#ifndef DISPLAY_H
#define DISPLAY_H

#include "../business/board.h"
#include "../business/player.h"

class Display
{
public:
    static void viewBoard(quoridor::Board & b);
    static void player(quoridor::Player & p);
    static char play();
    static quoridor::Direction chooseDirection();
    static quoridor::Orientation chooseOrientation();
    static quoridor::Position choosePosition();
};

#endif // DISPLAY_H
