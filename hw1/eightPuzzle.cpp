#include "eightPuzzle.h"

puzzle::puzzle(int *num) {
    for (int i = 0; i < NUM_LENGTH; i++) {
        number[i] = num[i];
    }
    this->lastLeaf = NULL;
    this->nextLeaf = NULL;
    this->parent = NULL;
}

void puzzle::init(int *target) {
    int tmp = 0;
    for (int i = 0; i < NUM_LENGTH; i++) {
        if (number[i] != target[i]) {
            tmp++;
        }
    }
    this->malDistance = tmp;
    if (this->parent == NULL) {
        this->depth = 0;
    } else {
        this->depth = this->parent->depth + 1;
    }
    this->evaluation = this->malDistance + this->depth;
}

void puzzle::setNum(int num[]) {
    for (int i = 0; i < NUM_LENGTH; i++) {
        this->number[i] = num[i];
    }
}

int* puzzle::getNum() {
    return this->number;
}

void puzzle::getNum(int *num) {
    for (int i = 0; i < NUM_LENGTH; i++) {
        num[i] = this->number[i];
    }
}

int puzzle::getMalDistance() {
    return this->malDistance;
}

int puzzle::getDepth() {
    return this->depth;
}

int puzzle::getEvaluation() {
    return this->evaluation;
}

void puzzle::print() {
    for (int i = 0; i < NUM_LENGTH; i++) {
        if ((i+1)%3 != 0) {
            cout << number[i] << ' ';
        } else {
            cout << number[i] << endl;
        }
    }
}

bool puzzle::isExistAnswer(int *target) {
    int countNum = 0, countTarget = 0;
    for (int i = 0; i < NUM_LENGTH; i++) {
        for (int j = 0; j < i; j++) {
            if ((this->number[j] < this->number[i]) && (this->number[j] != 0)) {
                countNum++;
            }
            if (target[j] < target[i] && target[j] != 0) {
                countTarget++;
            }
        }
    }
    return ((countNum + countTarget)%2 == 0);
}

bool puzzle::findTarget(int *target) {
    int i = 0;
    for (i = 0; i < NUM_LENGTH; i++) {
        if (this->number[i] != target[i]) {
            break;
        }
    }
    return i == NUM_LENGTH;
}

puzzle& puzzle::operator=(puzzle& eightPuzzle) {
    for (int i = 0; i < NUM_LENGTH; i++) {
        this->number[i] = eightPuzzle.getNum()[i];
    }
    this->malDistance = eightPuzzle.getMalDistance();
    this->depth = eightPuzzle.getDepth();
    this->evaluation = eightPuzzle.getEvaluation();

    return *this;
}

puzzle& puzzle::operator=(int other[NUM_LENGTH]) {
    for (int i = 0; i < NUM_LENGTH; i++) {
        this->number[i] = other[i];
    }

    this->malDistance = 0;
    this->depth = 0;
    this->evaluation = 0;

    return *this;
}

bool puzzle::operator==(puzzle& eightPuzzle) {
    bool result = true;
    for (int i = 0; i < NUM_LENGTH; i++) {
        if (this->number[i] != eightPuzzle.getNum()[i]) {
            result = false;
            break;
        }
    }
    return result;
}


bool puzzle::operator==(int other[NUM_LENGTH]) {
    bool result = true;
    for (int i = 0; i < NUM_LENGTH; i++) {
        if (this->number[i] != other[i]) {
            result = false;
            break;
        }
    }
    return result;
}
