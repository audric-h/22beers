#ifndef WALL_H
#define WALL_H

#include "orientation.h"

namespace quoridor {

class Wall {

private:

    Orientation orientation_;
    bool canBeHorizontal_;
    bool canBeVertical_;

public:

    Wall();
    bool setWall(Orientation o);
    void wallCantBeHorizontal();
    void wallCantBeVertical();
    void wallCanBeHorizontal();
    void wallCanBeVertical();
    Orientation getOrientation();
    void rollBack(bool hori, bool verti);
    bool getHorizontal();
    bool getVertical();

};


}
#endif // WALL_H
