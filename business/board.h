#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "wall.h"
#include "case.h"
#include "position.h"

namespace quoridor {

class Board {

private:

    static unsigned size;

    std::vector<std::vector<Wall>> wallss_;
    std::vector<std::vector<Case>> casess_;

public:

    static unsigned getSize();

    Board(unsigned s);
    Case & getCase(Position p);
    bool canIGoUp(Position p);
    bool canIGoDown(Position p);
    bool canIGoLeft(Position p);
    bool canIGoRight(Position p);
    bool setWall(Position p, Orientation o);
    void wallRollBack(Position p, Orientation o, bool hori, bool verti);
    void turnOffMarque();
    Wall & getWall(Position p);

private:

    bool sizeIsLegal(unsigned size);

};

}

#endif // BOARD_H
