#include "player.h"
#include "board.h"


namespace quoridor {

int Player::idCount = -1;

Player::Player(std::string name, unsigned nbWall) : position_(0,0) {
    idCount++;
    id_ = idCount;
    name_ = name;
    nbWall_ = nbWall;
    switch(id_) {
    case 0:
        position_ = Position(Board::getSize()-1,Board::getSize()/2);
        break;
    case 1:
        position_ = Position(0,Board::getSize()/2);
        break;
    case 2:
        position_ = Position(Board::getSize()/2,0);
        break;
    case 3:
        position_ = Position(Board::getSize()/2,Board::getSize()-1);
    }
}

unsigned Player::getId() const {
    return id_;
}

std::string Player::getName() const {
    return name_;
}

Position & Player::getPosition() {
    return position_;
}

bool Player::move(Direction d) {
    switch(d) {
    case Direction::UP:
        return position_.move(-1,0);
        break;
    case Direction::DOWN:
        return position_.move(1,0);
        break;
    case Direction::LEFT:
        return position_.move(0,-1);
        break;
    case Direction::RIGHT:
        return position_.move(0,1);
        break;
    default:
        return false;
        break;
    }
}

bool Player::isArrived() {
    switch(id_) {
    case 0:
        return position_.getRow() == 0;
        break;
    case 1:
        return position_.getRow() == Board::getSize()-1;
        break;
    case 2:
        return position_.getColumn() == Board::getSize()-1;
        break;
    case 3:
        return position_.getColumn() == 0;
        break;
    default:
        return false;
    }
}

unsigned Player::getNbWall() {
    return nbWall_;
}

void Player::nbWallDecremente() {
    nbWall_--;
}

}
