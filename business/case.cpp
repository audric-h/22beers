#include "case.h"

namespace quoridor {

Case::Case() {
    idPlayerOnMe_ = -1;
    marqued_ = false;
}

bool Case::isThereAPlayerOnMe() {
    return idPlayerOnMe_ != -1;
}

int Case::getIdPlayerOnMe() const {
    return idPlayerOnMe_;
}

void Case::setIdPlayerOnMe(int id) {
    idPlayerOnMe_ = id;
}

bool Case::isMarqued() const {
    return marqued_;
}

void Case::setMarqued() {
    marqued_ = true;
}

void Case::setNoMarqued() {
    marqued_ = false;
}

}
