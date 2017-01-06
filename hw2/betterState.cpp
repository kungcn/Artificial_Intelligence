#include "betterState.h"

betterState::betterState() {
    direction = 0;
    manhattan = 0;
}

betterState::betterState(int number, int position) {
    this->direction = number;
    this->manhattan = position;
}

bool betterState::operator<(const betterState &copy) const {
    return this->manhattan > copy.manhattan;
}

int betterState::getDirection() {
    return direction;
}

int betterState::getManhattan() {
    return manhattan;
}
