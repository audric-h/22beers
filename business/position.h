#ifndef POSITION_H
#define POSITION_H

namespace quoridor {

class Position {

private:

    unsigned row_;
    unsigned column_;

public:

    Position(unsigned row, unsigned column);
    unsigned getRow() const;
    unsigned getColumn() const;
    bool move(int row, int column);

};

}

#endif // POSITION_H
