//  eightQueen.cpp  four methods to solve eightQueen problem
//  author: KungChunNing
//  e-mail: kcnnow@gmail.com
//  date: 2016.10.06

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>

#define TESTCASE 100000
#define INITTEMPERATURE 80
#define MAXTIMESPERTEMP 500
#define ENDTEMPERATURE 0.0000001
#define COOLPERRATE 0.6

using namespace std;

double climbingTime;
double resetTime;
double coolingTime;
double firstChoiceTime;
int climbingFailTimes;
int resetFailTimes;
int firstChoiceFailTimes;
double coolingFailTimes;
double temperature;

int attackTheQueen(int *state) {
    int count = 0;
    for (int i = 0; i < 7; i++) {
        //  i, j同一位置冲突
        for (int j = i + 1; j < 8; j++)
            if (state[j] == state[i])
                count++;
        //  同一直线冲突
        for (int j = i + 1, k = state[i] + 1; j < 8 && k <= 8; j++, k++)
            if (state[j] == k)
                count++;
        //  同一对角线冲突
        for (int j = i + 1, k = state[i] - 1; j < 8 && k >= 1; j++, k--)
            if (state[j] == k)
                count++;
        }
    return count;
}

void killGoalByFirstChoice(int* state) {
    clock_t start = clock();
    int conflict = attackTheQueen(state);
    int bestRow = 0;
    int bestCol = 0;
    int tmp = 0;
    int record = 0;
    while (conflict != 0) {
        bestRow = -1;
        int stateNum = rand() % 8 + 1;
        record = state[stateNum];
        for (int j = 1; j <= 8; j++) {
            if (record != j) {
                state[stateNum] = j;
                tmp = attackTheQueen(state);
                if (conflict > tmp) {
                    conflict = tmp;
                    bestRow = stateNum;
                    bestCol = j;
                }
            }
        }
        state[stateNum] = record;
        if (bestRow == -1) {
            firstChoiceFailTimes++;
            return;
        } else {
            state[bestRow - 1] = bestCol;
        }
    }
    firstChoiceTime += (double)(clock() - start) / CLOCKS_PER_SEC;
}

void killGoalByClimbing(int* state) {
    clock_t start = clock();
    int conflict = attackTheQueen(state);
    int bestRow = 0;
    int bestCol = 0;
    int tmp = 0;
    int record = 0;
    while (conflict != 0) {
        bestRow = -1;
        for (int i = 1; i <= 8; i++) {
            record = state[i - 1];
            for (int j = 1; j <= 8; j++) {
                if (record != j) {
                    state[i - 1] = j;
                    tmp = attackTheQueen(state);
                    if (conflict > tmp) {
                        conflict = tmp;
                        bestRow = i;
                        bestCol = j;
                    }
                }
            }
            state[i - 1] = record;
        }
        if (bestRow == -1) {
            climbingFailTimes++;
            return;
        } else {
            state[bestRow - 1] = bestCol;
        }
    }
    climbingTime += (double)(clock() - start) / CLOCKS_PER_SEC;
}

void killGoalByReset(int* state) {
    clock_t start = clock();
    int conflict = attackTheQueen(state);
    int bestRow = 0;
    int bestCol = 0;
    int tmp = 0;
    int record = 0;
    while (conflict != 0) {
        bestRow = -1;
        for (int i = 1; i <= 8; i++) {
            record = state[i - 1];
            for (int j = 1; j <= 8; j++) {
                if (record != j) {
                    state[i - 1] = j;
                    tmp = attackTheQueen(state);
                    if (conflict > tmp) {
                        conflict = tmp;
                        bestRow = i;
                        bestCol = j;
                    }
                }
            }
            state[i - 1] = record;
        }
        if (bestRow == -1) {
            for (int k = 0; k < 8; k++) {
                state[k] = rand() % 8 + 1;
            }
            conflict = attackTheQueen(state);
        } else {
            state[bestRow - 1] = bestCol;
        }
    }
    resetTime += (double)(clock() - start) / CLOCKS_PER_SEC;
}

void killGoalByCooling(int* state) {
    clock_t start = clock();
    int conflict = attackTheQueen(state);
    int bestRow = 0;
    int bestCol = 0;
    int tmp = 0;
    int record = 0;
    int tryTimes = MAXTIMESPERTEMP;
    int tryConflict = 0;
    temperature = INITTEMPERATURE;
    while (conflict != 0) {
        tryConflict = 28;
        for (int i = 1; i <= 8; i++) {
            record = state[i - 1];
            for (int j = 1; j <= 8; j++) {
                if (record != j) {
                    state[i - 1] = j;
                    tmp = attackTheQueen(state);
                    if (conflict > tmp) {
                        tryConflict = tmp;
                        bestRow = i;
                        bestCol = j;
                    }
                }
            }
            state[i - 1] = record;
        }
        tryTimes--;
        if (tryTimes == 0) {
            tryTimes = MAXTIMESPERTEMP;
            temperature *= COOLPERRATE;
        }
        if ((!(temperature < ENDTEMPERATURE) && (tryConflict < conflict || ((double)(rand() % 1000) / 1000) < exp(tryConflict / temperature)))) {
            state[bestRow - 1] = bestCol;
            conflict = tryConflict;
        } else {
            coolingFailTimes++;
            return;
        }
    }
    coolingTime += (double)(clock() - start) / CLOCKS_PER_SEC;
}

void killEightQueen() {
    ifstream ifs;
    ifs.open ("eightQueen.txt", std::ifstream::in);

    int state[8];

    char temp[20];
    ifs.getline(temp, 20);
    string tmp = temp;
    while (ifs.good()) {
        for (int i = 0, j = 0; i < tmp.length(), j < 8; i++) {
            if (i % 2 == 0) {
                state[j] = tmp[i] - '0';
                j++;
            }
        }
        killGoalByClimbing(state);
        killGoalByFirstChoice(state);
        killGoalByReset(state);
        killGoalByCooling(state);
        ifs.getline(temp, 20);
        tmp = temp;
    }
    ifs.close();
}

void print() {
    cout << "最陡上升法解决有解八皇后的平均时间为:" << climbingTime / (double)(TESTCASE - climbingFailTimes) << endl;
    cout << "最陡上升法解决八皇后问题的成功率为:" << 1 - (double)climbingFailTimes / (double)TESTCASE << endl;
    cout << "首选爬山法解决有解八皇后的平均时间为:" << firstChoiceTime / (double)(TESTCASE - firstChoiceFailTimes) << endl;
    cout << "首选爬山法解决八皇后问题的成功率为:" << 1 - (double)firstChoiceFailTimes / (double)TESTCASE << endl;
    cout << "随机重启爬山法解决有解八皇后的平均时间为:" << resetTime / (double)(TESTCASE - resetFailTimes) << endl;
    cout << "随机重启爬山法解决八皇后问题的成功率为:" << 1 - (double)resetFailTimes / (double)TESTCASE << endl;
    cout << "模拟退火法解决有解八皇后的平均时间为:" << coolingTime / (double)(TESTCASE - coolingFailTimes) << endl;
    cout << "模拟退火法解决八皇后问题的成功率为:" << 1 - (double)coolingFailTimes / (double)TESTCASE << endl;
}

int main(void) {
    climbingTime = 0;
    climbingFailTimes = 0;
    firstChoiceTime = 0;
    firstChoiceFailTimes = 0;
    resetTime = 0;
    coolingTime = 0;
    coolingFailTimes = 0;
    killEightQueen();
    print();
    return 0;
}

