#include <iostream>
#include <ctime>
#include <cstdlib>
#include "eightPuzzle.h"

using namespace std;

bool moveUp(int *number) {
    int i = 0;
    for (i = 0; i < NUM_LENGTH; i++) {
        if (number[i] == 0) {
            break;
        }
    }
    if (i < 3) {
        return false;
    } else {
        number[i] = number[i - 3];
        number[i - 3] = 0;
    }
    return true;
}

bool moveDown(int *number) {
    int i = 0;
    for (i = 0; i < NUM_LENGTH; i++) {
        if (number[i] == 0) {
            break;
        }
    }
    if (i > 5) {
        return false;
    } else {
        number[i] = number[i + 3];
        number[i + 3] = 0;
    }
    return true;
}

bool moveLeft(int *number) {
    int i = 0;
    for (i = 0; i < NUM_LENGTH; i++) {
        if (number[i] == 0) {
            break;
        }
    }
    if (i == 0 || i == 3 || i == 6) {
        return false;
    } else {
        number[i] = number[i - 1];
        number[i - 1] = 0;
    }
    return true;
}

bool moveRight(int *number) {
    int i = 0;
    for (i = 0; i < NUM_LENGTH; i++) {
        if (number[i] == 0) {
            break;
        }
    }
    if (i == 2 || i == 5 || i == 8) {
        return false;
    } else {
        number[i] = number[i + 1];
        number[i + 1] = 0;
    }
    return true;
}

bool existed(int *num, puzzle *init) {
    puzzle *tmp;
    for (tmp = init; tmp != NULL; tmp = tmp->parent) {
        if (*tmp == num) {
            return true;
        }
    }
    return false;
}

puzzle *bestRoute(puzzle *init, puzzle *target) {
    puzzle *tmp, *best;
    tmp = best = init;
    init->init(target->getNum());
    int min = init->getEvaluation();
    for (tmp = init; tmp != NULL; tmp = tmp->nextLeaf) {
        if (min > tmp->getEvaluation()) {
            best = tmp;
            min = tmp->getEvaluation();
        }
    }
    return best;
}

void printRoute(puzzle *best, int listLength) {
    int step = 0;
    puzzle *tmp;
    for (tmp = best->parent; tmp != NULL; tmp = tmp->parent) {
        cout << "第" << step + 1 << "次序列为" << endl;
        tmp->print();
        step++;
    }
    cout << "总次数为" << step << endl;
    cout << "内存开销为" << listLength << endl;
    return;
}


void processing(puzzle &init, puzzle &target) {
    if (!init.isExistAnswer(target.getNum())) {
        cout << "无解" << endl;
        return;
    }
    puzzle *best = &init;
    puzzle *list = &init;
    puzzle *apply, *temp;
    int tmp[NUM_LENGTH], listLength = 0;
    while (best != NULL) {
        best = bestRoute(list, &target);
        if (best->findTarget(target.getNum())) {
            printRoute(best, listLength);
            return;
        }
        temp = best->lastLeaf;
        best->getNum(tmp);
        if (moveUp(tmp) && !existed(tmp, best)) {
            apply = new puzzle(tmp);
            apply->parent = best;
            apply->init(target.getNum());
            apply->lastLeaf = temp;
            if (temp == NULL) {
                list = apply;
            } else {
                temp->nextLeaf = apply;
            }
            temp = apply;
            listLength++;
        }
        best->getNum(tmp);
        if (moveDown(tmp) && !existed(tmp, best)) {
            apply = new puzzle(tmp);
            apply->parent = best;
            apply->init(target.getNum());
            apply->lastLeaf = temp;
            if (temp == NULL) {
                list = apply;
            } else {
                temp->nextLeaf = apply;
            }
            temp = apply;
            listLength++;
        }
        best->getNum(tmp);
        if (moveLeft(tmp) && !existed(tmp, best)) {
            apply = new puzzle(tmp);
            apply->parent = best;
            apply->init(target.getNum());
            apply->lastLeaf = temp;
            if (temp == NULL) {
                list = apply;
            } else {
                temp->nextLeaf = apply;
            }
            temp = apply;
            listLength++;
        }
        best->getNum(tmp);
        if (moveRight(tmp) && !existed(tmp, best)) {
            apply = new puzzle(tmp);
            apply->parent = best;
            apply->init(target.getNum());
            apply->lastLeaf = temp;
            if (temp == NULL) {
                list = apply;
            } else {
                temp->nextLeaf = apply;
            }
            temp = apply;
            listLength++;
        }
        temp->nextLeaf = best->nextLeaf;
        if (best->nextLeaf != NULL) {
            best->nextLeaf->lastLeaf = temp;
        }
        best->nextLeaf= best->lastLeaf = NULL;
    }
}

int main(void) {
    double time;
    clock_t start, end;

    int num[NUM_LENGTH];
    cout << "请输入起始状态的矩阵,用0代表空格" << endl;
    for (int i = 0; i < NUM_LENGTH; i++) {
        cin >> num[i];
        if (num[i] < 0 || num[i] > 8) {
            cout << "只能输入0-8之间的数字,请重新输入" << endl;
            i--;
        }
        for (int j = 0; j < i; j++) {
            if (num[i] == num[j]) {
                cout << "数字不能重复,请重新输入" << endl;
                i--;
            }
        }
    }

    puzzle *init = new puzzle(num);
    int targetArray[NUM_LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    puzzle *target = new puzzle(targetArray);

    cout << "初始状态为:" << endl;
    init->print();
    cout << "最后状态是:" << endl;
    target->print();

    start = clock();
    processing(*init, *target);
    end = clock();
    time = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
    cout << "总时间开销: " << time << " " << "millisec." << endl;
    return 0;
}
