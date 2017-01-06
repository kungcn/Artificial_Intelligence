//  eightPuzzle.cpp four methods to solve eightPuzzle problem
//  author: KungChunNing
//  e-mail: kcnnow@gmail.com
//  date: 2016.10.08

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include "betterState.h"

#define TESTCASE 100000
#define MAXTIMESPERTEMP 300
#define ENDTEMPERATURE 0.000000001
#define COOLPERRATE 0.8
#define INITTEMPERATURE 10
#define STEP 1000

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

using namespace std;

double climbingTime;
double firstChoiceTime;
double resetTime;
double coolingTime;
int climbingFailTimes;
int firstChoiceFailTimes;
int coolingFailTimes;
int resetFailTimes;
int betterManhattan;
double temperature;

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int manhattanDistance(int number, int position) {
    int destinationX = ceil(number / 3);
    int destinationY = (number - 1) % 3 + 1;
    int positionX = ceil(position / 3);
    int positionY = (position - 1) % 3 + 1;

    return abs(destinationX - positionX) + abs(destinationY - positionY);
}

bool done(int* state) {
    for (int i = 0; i < 8; i++) {
        if (state[i] != i + 1)
            return false;
    }
    return true;
}

bool betterOrNot(int *state, int position, int direction) {
    switch (direction) {
    case UP:
        if (position <= 3) {
            return false;
        } else {
            betterManhattan =  manhattanDistance(state[position - 4], position - 3) - manhattanDistance(state[position - 4], position);
                return manhattanDistance(state[position - 4], position - 3) > manhattanDistance(state[position - 4], position);
            }
        case DOWN:
            if (position >= 7) {
                return false;
            } else {
                betterManhattan = manhattanDistance(state[position + 2], position + 3) - manhattanDistance(state[position + 2], position);
                return manhattanDistance(state[position + 2], position + 3) > manhattanDistance(state[position + 2], position);
            }
        case LEFT:
            if (position % 3 == 1)
                return false;
            else {
                betterManhattan = manhattanDistance(state[position - 2], position - 1) - manhattanDistance(state[position - 2], position);
                return manhattanDistance(state[position - 2], position - 1) > manhattanDistance(state[position - 2], position);
            }
        case RIGHT:
            if (position % 3 == 0) {
                return false;
            } else {
                betterManhattan = manhattanDistance(state[position], position + 1) - manhattanDistance(state[position], position);
                return manhattanDistance(state[position], position + 1) > manhattanDistance(state[position], position);
            }
    }
    return false;
}

bool betterOrNotInCooling(int *state, int position, int direction) {
    int betterManhattan;
    switch (direction) {
        case UP:
            if (position <= 3)
                return false;
            else {
                betterManhattan = manhattanDistance(state[position - 4], position - 3) - manhattanDistance(state[position - 4], position);
                return (betterManhattan > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(betterManhattan / temperature);
            }
        case DOWN:
            if (position >= 7)
                return false;
            else {
                betterManhattan = manhattanDistance(state[position + 2], position + 3) - manhattanDistance(state[position + 2], position);
                return (betterManhattan > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(betterManhattan / temperature);
            }
        case LEFT:
            if (position % 3 == 1)
                return false;
            else {
                betterManhattan = manhattanDistance(state[position - 2], position - 1) - manhattanDistance(state[position - 2], position);
                return (betterManhattan > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(betterManhattan / temperature);
            }
        case RIGHT:
            if (position % 3 == 0)
                return false;
            else {
                betterManhattan = manhattanDistance(state[position], position + 1) - manhattanDistance(state[position], position);
                return (betterManhattan > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(betterManhattan / temperature);
            }
    }
    return false;
}

void randomAgain(int *newState) {
    int state[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    int steps;
    int position;
    int direction;
    steps = STEP;
    position = 9;
    while (steps--) {
        direction = rand() % 4;
        switch (direction) {
        case UP:
            if (position <= 3)
                break;
            else {
                swap(state[position - 1], state[position - 4]);
                position -= 3;
                break;
            }
        case DOWN:
            if (position >= 7)
                break;
            else {
                swap(state[position - 1], state[position + 2]);
                position += 3;
                break;
            }
        case LEFT:
            if (position % 3 == 1)
                break;
            else {
                swap(state[position - 1], state[position - 2]);
                position--;
                break;
            }
        case RIGHT:
            if (position % 3 == 0)
                break;
            else {
                swap(state[position - 1], state[position]);
                position++;
                break;
            }
        }
    }
    for (int i = 0; i < 9; i++)
        newState[i] = state[i];
}

void killGoalByClimbing(int* state) {
    clock_t start = clock();
    int position;
    int i;
    for (i = 0; i < 9; i++) {
        if (state[i] == 0) {
            position = i + 1;
            break;
        }
    }
    while (!done(state)) {
        bool haveNot = false;
        std::vector<betterState> better;
        for (i = 0; i < 4; i++) {
            if (betterOrNot(state, position, i)) {
                haveNot = true;
                better.push_back(betterState(i, betterManhattan));
            }
            if (i == 3 && haveNot) {
                std::sort(better.begin(), better.end());
                switch (better[0].getDirection()) {
                case UP:
                    swap(state[position - 1], state[position - 4]);
                    position -= 3;
                    break;
                case DOWN:
                    swap(state[position - 1], state[position + 2]);
                    position += 3;
                    break;
                case LEFT:
                    swap(state[position - 1], state[position - 2]);
                    position--;
                    break;
                case RIGHT:
                    swap(state[position - 1], state[position]);
                    position++;
                    break;
                }
            }
        }
        if (!haveNot) {
            climbingFailTimes++;
            return;
        }
    }
    climbingTime += (double)(clock() - start) / CLOCKS_PER_SEC;
}

void killGoalByFirstChoice(int* state) {
    clock_t start = clock();
    int position;
    int i;
    for (i = 0; i < 9; i++) {
        if (state[i] == 0) {
            position = i + 1;
            break;
        }
    }
    while (!done(state)) {
        bool haveNot = false;
        std::vector<betterState> better;
        i = rand() % 4 + 1;
        if (betterOrNot(state, position, i)) {
            haveNot = true;
            better.push_back(betterState(i, betterManhattan));
        }
        if (haveNot) {
            std::sort(better.begin(), better.end());
            switch (better[0].getDirection()) {
            case UP:
                swap(state[position - 1], state[position - 4]);
                position -= 3;
                break;
            case DOWN:
                swap(state[position - 1], state[position + 2]);
                position += 3;
                break;
            case LEFT:
                swap(state[position - 1], state[position - 2]);
                position--;
                break;
            case RIGHT:
                swap(state[position - 1], state[position]);
                    position++;
                    break;
            }
        }
        if (!haveNot) {
            firstChoiceFailTimes++;
            return;
        }
    }
    firstChoiceTime += (double)(clock() - start) / CLOCKS_PER_SEC;
}

void killGoalByReset(int* state) {
    clock_t start = clock();
    int position;
    int i;
    for (i = 0; i < 9; i++) {
        if (state[i] == 0) {
            position = i + 1;
            break;
        }
    }
    while (!done(state)) {
        bool haveNot = false;
        std::vector<betterState> better;
        for (i = 0; i < 4; i++) {
            if (betterOrNot(state, position, i)) {
                haveNot = true;
                better.push_back(betterState(i, betterManhattan));
            }
            if (i == 3 && haveNot) {
                std::sort(better.begin(), better.end());
                switch (better[0].getDirection()) {
                case UP:
                    swap(state[position - 1], state[position - 4]);
                    position -= 3;
                    break;
                case DOWN:
                    swap(state[position - 1], state[position + 2]);
                    position += 3;
                    break;
                case LEFT:
                    swap(state[position - 1], state[position - 2]);
                    position--;
                    break;
                case RIGHT:
                    swap(state[position - 1], state[position]);
                    position++;
                    break;
                }
            }
        }
        if (!haveNot) {
            randomAgain(state);
        }
    }
    resetTime += (double)(clock() - start) / CLOCKS_PER_SEC;
}

void killGoalByCooling(int* state) {
    clock_t start = clock();
    int position;
    int i;
    bool haveNot;
    for (i = 0; i < 9; i++) {
        if (state[i] == 0) {
            position = i + 1;
            break;
        }
    }
    temperature = INITTEMPERATURE;
    int tryTimes = MAXTIMESPERTEMP;
    while (!done(state)) {
        haveNot = false;
        for (i = 0; i < 4; i++)
            if (betterOrNotInCooling(state, position, i)) {
                haveNot = true;
                switch (i) {
                    case UP:
                        swap(state[position - 1], state[position - 4]);
                        position -= 3;
                        break;
                    case DOWN:
                        swap(state[position - 1], state[position + 2]);
                        position += 3;
                        break;
                    case LEFT:
                        swap(state[position - 1], state[position - 2]);
                        position--;
                        break;
                    case RIGHT:
                        swap(state[position - 1], state[position]);
                        position++;
                        break;
                }
                break;
            }
            tryTimes--;
        if (tryTimes == 0) {
            tryTimes = MAXTIMESPERTEMP;
            temperature *= COOLPERRATE;
        }
        if (!haveNot || temperature < ENDTEMPERATURE) {
            coolingFailTimes++;
            return;
        }
    }
    coolingTime += (double)(clock() - start) / CLOCKS_PER_SEC;
}

void killEightPuzzle() {
    ifstream ifs;
    ifs.open ("eightPuzzle.txt", std::ifstream::in);

    int state[9];

    char temp[20];
    ifs.getline(temp, 20);
    string tmp = temp;
    while (ifs.good()) {
        for (int i = 0, j = 0; i < tmp.length(), j < 9; i++) {
            if (i % 2 == 0) {
                state[j] = tmp[i] - '0';
                j++;
            }
        }
        killGoalByClimbing(state);
        killGoalByFirstChoice(state);
        //killGoalByReset(state);
        //killGoalByCooling(state);
        ifs.getline(temp, 20);
        tmp = temp;
    }
    ifs.close();
}

void print() {
    cout << "最陡上升法解决有解八数码的平均时间为:" << climbingTime / (double)(TESTCASE - climbingFailTimes) << endl;
    cout << "最陡上升法解决八数码问题的成功率为:" << 1 - (double)climbingFailTimes / (double)TESTCASE << endl;
    cout << "首选爬山法解决有解八数码的平均时间为:" << firstChoiceTime / (double)(TESTCASE - firstChoiceFailTimes) << endl;
    cout << "首选爬山法解决八数码问题的成功率为:" << 1 - (double)firstChoiceFailTimes / (double)TESTCASE << endl;
    cout << "随机重启爬山法解决有解八数码的平均时间为:" << resetTime / (double)(TESTCASE - resetFailTimes) << endl;
    cout << "随机重启爬山法解决八数码问题的成功率为:" << 1 - (double)resetFailTimes / (double)TESTCASE << endl;
    cout << "模拟退火法解决有解八数码的平均时间为:" << coolingTime / (double)(TESTCASE - coolingFailTimes) << endl;
    cout << "模拟退火法解决八数码问题的成功率为:" << 1 - (double)coolingFailTimes / (double)TESTCASE << endl;
}

int main(void) {
    climbingTime = 0;
    climbingFailTimes = 0;
    firstChoiceTime = 0;
    firstChoiceFailTimes = 0;
    resetTime = 0;
    coolingTime = 0;
    coolingFailTimes = 0;

    killEightPuzzle();

    print();
    return 0;
}
