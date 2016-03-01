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
    std::string name_;
    Position position_;

public:

    Player(std::string name);
    unsigned getId() const;
    std::string getName() const;
    Position & getPosition();
    bool move(Direction d);
    bool isArrived();

};

}
#endif // PLAYER_H
