#include "board.h"
#include <iostream>

namespace quoridor {

unsigned Board::size = 9;

Board::Board(unsigned s) {
    if(!sizeIsLegal(s)) throw std::invalid_argument { "Taille du plateau de jeu invalide." };
    size = s;
    for(unsigned i=0; i<getSize(); i++) {
        std::vector<Case> casesTemp;
        for(unsigned j=0; j<getSize(); j++) {
            Case c;
            casesTemp.push_back(c);
        }
        casess_.push_back(casesTemp);
    }
    for(unsigned i=0; i<getSize()-1; i++) {
        std::vector<Wall> wallsTemp;
        for(unsigned j=0; j<getSize()-1; j++) {
            Wall w;
            wallsTemp.push_back(w);
        }
        wallss_.push_back(wallsTemp);
    }
}

unsigned Board::getSize() {
    return size;
}


bool Board::sizeIsLegal(unsigned size) {
    return (size % 2 == 1 && size >= 5 && size <= 19);
}

bool Board::canIGoUp(Position p) {
    if(p.getRow() == 0) return false;
    if(p.getColumn() == 0) {
        return wallss_[p.getRow()-1][p.getColumn()].getOrientation() != Orientation::HORIZONTAL;
    } else if(p.getColumn() == Board::getSize()-1) {
        return wallss_[p.getRow()-1][p.getColumn()-1].getOrientation() != Orientation::HORIZONTAL;
    } else {
        return ( (wallss_[p.getRow()-1][p.getColumn()].getOrientation() != Orientation::HORIZONTAL) &&
                 (wallss_[p.getRow()-1][p.getColumn()-1].getOrientation() != Orientation::HORIZONTAL) );
    }
}

bool Board::canIGoDown(Position p) {
    if(p.getRow() == getSize()-1) return false;
    if(p.getColumn() == 0) {
        return wallss_[p.getRow()][p.getColumn()].getOrientation() != Orientation::HORIZONTAL;
    } else if(p.getColumn() == Board::getSize()-1) {
        return wallss_[p.getRow()][p.getColumn()-1].getOrientation() != Orientation::HORIZONTAL;
    } else {
        return ( (wallss_[p.getRow()][p.getColumn()].getOrientation() != Orientation::HORIZONTAL) &&
                 (wallss_[p.getRow()][p.getColumn()-1].getOrientation() != Orientation::HORIZONTAL) );
    }
}

bool Board::canIGoLeft(Position p) {
    if(p.getColumn() == 0) return false;
    if(p.getRow() == 0) {
        return wallss_[p.getRow()][p.getColumn()-1].getOrientation() != Orientation::VERTICAL;
    } else if(p.getRow() == getSize()-1) {
        return wallss_[p.getRow()-1][p.getColumn()-1].getOrientation() != Orientation::VERTICAL;
    } else {
        return ( (wallss_[p.getRow()][p.getColumn()-1].getOrientation() != Orientation::VERTICAL) &&
                 (wallss_[p.getRow()-1][p.getColumn()-1].getOrientation() != Orientation::VERTICAL) );
    }
}

bool Board::canIGoRight(Position p) {
    if(p.getColumn() == getSize()-1) return false;
    if(p.getRow() == 0) {
        return wallss_[p.getRow()][p.getColumn()].getOrientation() != Orientation::VERTICAL;
    } else if(p.getRow() == getSize()-1) {
        return wallss_[p.getRow()-1][p.getColumn()].getOrientation() != Orientation::VERTICAL;
    } else {
        return ( (wallss_[p.getRow()][p.getColumn()].getOrientation() != Orientation::VERTICAL) &&
                 (wallss_[p.getRow()-1][p.getColumn()].getOrientation() != Orientation::VERTICAL) );
    }
}

Case & Board::getCase(Position p) {
    return casess_[p.getRow()][p.getColumn()];
}

bool Board::setWall(Position p, Orientation o) {
    if(wallss_[p.getRow()][p.getColumn()].getOrientation() != Orientation::NOTDEFINED) return false;
    bool wallPlaced = false;
    wallPlaced = wallss_[p.getRow()][p.getColumn()].setWall(o);
    if(wallPlaced) {
        switch(o) {
        case Orientation::HORIZONTAL:
            if(p.getColumn() > 0) wallss_[p.getRow()][p.getColumn()-1].wallCantBeHorizontal();
            if(p.getColumn()+1 < Board::getSize()-1) wallss_[p.getRow()][p.getColumn()].wallCantBeHorizontal();
            break;
        case Orientation::VERTICAL:
            if(p.getRow() > 0) wallss_[p.getRow()-1][p.getColumn()].wallCantBeVertical();
            if(p.getRow()+1 < Board::getSize()-1) wallss_[p.getRow()+1][p.getColumn()].wallCantBeVertical();
            break;
        }
    }
    return wallPlaced;
}

void Board::wallRollBack(Position p, Orientation o) {
    wallss_[p.getRow()][p.getColumn()].rollBack();
    switch(o) {
    case Orientation::HORIZONTAL:
        if(p.getColumn() > 0) wallss_[p.getRow()][p.getColumn()-1].wallCanBeHorizontal();
        if(p.getColumn()+1 < Board::getSize()-1) wallss_[p.getRow()][p.getColumn()].wallCanBeHorizontal();
        break;
    case Orientation::VERTICAL:
        if(p.getRow() > 0) wallss_[p.getRow()-1][p.getColumn()].wallCanBeVertical();
        if(p.getRow()+1 < Board::getSize()-1) wallss_[p.getRow()+1][p.getColumn()].wallCanBeVertical();
        break;
    }
}

void Board::turnOffMarque() {
    for(unsigned i=0; i<size; i++)
        for(unsigned j=0; j<size; j++) {
            casess_[i][j].setNoMarqued();
        }
}

Wall & Board::getWall(Position p) {
    return wallss_[p.getRow()][p.getColumn()];
}

}

