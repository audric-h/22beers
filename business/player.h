#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "position.h"
#include "direction.h"

namespace quoridor {


class Player {

private:

    static int idCount;

    unsigned id_;
    unsigned nbWall_;
    std::string name_;
    Position position_;

public:

    Player(std::string name, unsigned nbWall);
    unsigned getId() const;
    std::string getName() const;
    Position & getPosition();
    bool move(Direction d);
    bool isArrived();
    unsigned getNbWall();
    void nbWallDecremente();

};

}
#endif // PLAYER_H
