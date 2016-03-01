#include "wall.h"

namespace quoridor {

Wall::Wall() {
    orientation_ = Orientation::NOTDEFINED;
    canBeHorizontal_ = true;
    canBeVertical_ = true;
}

bool Wall::setWall(Orientation o) {
    switch(o) {
    case Orientation::HORIZONTAL:
        if(canBeHorizontal_) {
            orientation_ = o;
            return true;
        } else {
            return false;
        }
        break;
    case Orientation::VERTICAL:
        if(canBeVertical_) {
            orientation_ = o;
            return true;
        } else {
            return false;
        }
        break;
    case Orientation::NOTDEFINED:
        break;
    }
    return false;
}

void Wall::wallCantBeHorizontal() {
    canBeHorizontal_ = false;
}

void Wall::wallCantBeVertical() {
    canBeVertical_ = false;
}

void Wall::wallCanBeHorizontal() {
    canBeHorizontal_ = true;
}

void Wall::wallCanBeVertical() {
    canBeVertical_ = true;
}

Orientation Wall::getOrientation() {
    return orientation_;
}

void Wall::rollBack() {
    orientation_ = Orientation::NOTDEFINED;
}

bool Wall::getHorizontal() {
    return canBeHorizontal_;
}

bool Wall::getVertical() {
    return canBeVertical_;
}

}
