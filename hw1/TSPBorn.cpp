#include <iostream>
#include <cstdlib>

#define CITY_NUMBER 8
#define CITY_DISTANCE 9
#define INFINITE 200
#define random(x) (rand()%x)
using namespace std;

void print(int cityArray[][CITY_NUMBER]) {
    for (int i = 0; i < CITY_NUMBER; i++) {
        for (int j = 0; j < CITY_NUMBER; j++) {
            cout << cityArray[i][j] << ' ';
        }
        cout << endl;
    }
}

int main(void) {
    int cityArray[CITY_NUMBER][CITY_NUMBER];
    for (int i = 0; i < CITY_NUMBER; i++) {
        for (int j = 0; j < CITY_NUMBER; j++) {
            if (i == j) {
                cityArray[i][j] = INFINITE;
            }
            if (i < j) {
                cityArray[i][j] = random(CITY_DISTANCE) + 1;
            }
        }
    }
    for (int i = 0; i < CITY_NUMBER; i++) {
        for (int j = 0; j < CITY_NUMBER; j++) {
            if (i > j) {
                cityArray[i][j] = cityArray[j][i];
            }
        }
    }
    print(cityArray);
    return 0;
}
