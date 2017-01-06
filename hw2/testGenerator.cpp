//  testGenerator.cpp  to generate big data about eightQueen and eightPuzzle
//  author: KungChunNing
//  e-mail: kcnnow@gmail.com
//  date: 2016.10.06

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#define TESTCASE 100000
#define STEP 1000

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

using namespace std;

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void eightQueenGenerator(const char* filename) {
  ofstream ofs;
  ofs.open(filename, std::ofstream::out);

  int state[8] = {0};
  int position = 0;
  for (int i = 0; i < TESTCASE; i++) {
      for (int j = 0; j < 8; j++) {
          state[j] = rand() % 8 + 1;
          ofs << state[j] << (j < 7 ? " " : "\n");
      }
  }
  if (ofs.good())
      cout << "成功随机生成八皇后" << TESTCASE << "个" << endl;
  ofs.close();
}

void eightPuzzleGenerator(const char* filename) {
    ofstream ofs;
    ofs.open(filename, std::ofstream::out);

    for (int i = 0; i < TESTCASE; i++) {
        int finalState[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        int position = 9;
        int direction = 5;
        for (int j = 0; j < STEP; j++) {
            direction = rand() % 4;
            switch (direction) {
            case UP:
                //  顶端不能再往上走
                if (position > 3) {
                    swap(finalState[position - 1], finalState[position - 4]);
                    position -= 3;
                }
                break;
                //  低端不能再往下行
            case DOWN:
                if (position < 7) {
                    swap(finalState[position - 1], finalState[position + 2]);
                    position += 3;
                }
                break;
                //  左端不能再左行
            case LEFT:
                if (position % 3 != 1) {
                    swap(finalState[position - 1], finalState[position - 2]);
                    position--;
                }
                break;
                //  右端不能再右走
            case RIGHT:
                if (position % 3 != 0) {
                    swap(finalState[position - 1], finalState[position + 1]);
                    position++;
                }
                break;
            };
        }
        for (int k = 0; k < 9; k++)
            ofs << finalState[k] << (k < 8 ? " " : "\n");
    }
    if (ofs.good())
        cout << "成功随机生成八数码" << TESTCASE << "个" << endl;
    ofs.close();
}

int main(void) {
    cout << "开始随机生成八皇后和八数码" << endl;
    eightQueenGenerator("eightQueen.txt");
    eightPuzzleGenerator("eightPuzzle.txt");
    return 0;
}
