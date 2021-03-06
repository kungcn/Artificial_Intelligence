#include <iostream>
#include <ctime>
#include <cstdlib>

#define SAMPLE_NUMBER 1000000
#define N 999

using namespace std;

double rejectionSampling() {
    //  init variables
    bool B[SAMPLE_NUMBER] = {false};
    bool E[SAMPLE_NUMBER] = {false};
    bool A[SAMPLE_NUMBER] = {false};
    bool J[SAMPLE_NUMBER] = {false};
    bool M[SAMPLE_NUMBER] = {false};
    int den = 0; // denominator
    int num = 0; // numerator

    for (int i = 0; i < SAMPLE_NUMBER; i++)
        if ((rand()%(N+1) / (double)N) < 0.001)
            B[i] = true;

    for (int i = 0; i < SAMPLE_NUMBER; i++)
        if ((rand()%(N+1) / (double)N) < 0.002)
            E[i] = true;

    for (int i = 0; i < SAMPLE_NUMBER; i++) {
        double random = rand()%(N+1) / (double)N;
        if (B[i] == true && E[i] == true && random < 0.95)
            A[i] = true;
        else if (B[i] == true && E[i] == false && random < 0.94)
            A[i] = true;
        else if (B[i] == false && E[i] == true && random < 0.29)
            A[i] = true;
        else if (B[i] == false && E[i] == false && random < 0.001)
            A[i] = true;
    }

    for (int i = 0; i < SAMPLE_NUMBER; i++) {
        double random = rand()%(N+1) / (double)N;
        if (A[i] == true && random < 0.9)
            J[i] = true;
        else if (A[i] == false && random < 0.05)
            J[i] = true;
    }

    for (int i = 0; i < SAMPLE_NUMBER; i++) {
        double random = rand()%(N+1) / (double)N;
        if (A[i] == true && random < 0.7)
            M[i] = true;
        else if (A[i] == false && random < 0.01)
            M[i] = true;
    }

    for (int i = 0; i < SAMPLE_NUMBER; i++) {
        if (J[i] == true && M[i] == true) {
            den++;
            if (B[i] == true) {
                num++;
            }
        }
    }
    return num/(double)den;
}

int main(void) {
    srand( (unsigned)time(NULL));
    cout << "The probability from direct sample is: " << rejectionSampling() << endl;
    return 0;
}
