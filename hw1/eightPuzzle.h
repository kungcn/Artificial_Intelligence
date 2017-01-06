#ifndef EIGHTPUZZLE
#define EIGHTPUZZLE


#include <iostream>
#include <cstdlib>
#include <ctime>

#define NUM_LENGTH 9

using namespace std;

class puzzle {

  private:
    int number[NUM_LENGTH];
    int malDistance;
    int depth;
    int evaluation;

  public:
    puzzle *parent;
    puzzle *lastLeaf;
    puzzle *nextLeaf;
    puzzle(int *num);
    void init(int *target);
    void setNum(int num[]);
    int* getNum();
    void getNum(int *num);
    int getMalDistance();
    int getDepth();
    int getEvaluation();
    void print();
    bool isExistAnswer(int *target);
    bool findTarget(int *target);
    puzzle& operator=(puzzle& eightPuzzle);
    puzzle& operator=(int other[NUM_LENGTH]);
    bool operator==(puzzle& eightPuzzle);
    bool operator==(int other[NUM_LENGTH]);
};

#endif
