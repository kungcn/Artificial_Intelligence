#include <iostream>
#include <ctime>
#include <cstdlib>

#define SAMPLE_NUMBER 100000
#define N 999

using namespace std;

double likelihoodWeighting() {
     //  init variables
    bool B[SAMPLE_NUMBER] = {false};
    bool E[SAMPLE_NUMBER] = {false};
    bool A[SAMPLE_NUMBER] = {false};
    bool J[SAMPLE_NUMBER] = {false};
    bool M[SAMPLE_NUMBER] = {false};
    double den = 0; // denominator
    double num = 0; // numerator
    double w[SAMPLE_NUMBER];

    for (int i = 0; i < SAMPLE_NUMBER; i++)
        w[i] = 1;

    for (int i = 0; i < SAMPLE_NUMBER; i++)
        if ((rand()%(N+1) / (double)N) < 0.001) {
            B[i] = true;
        }

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
        if (A[i] == true && random < 0.9) {
          w[i] = w[i] * 0.9;
        }
        else if (A[i] == false && random < 0.05) {
          w[i] = w[i] * 0.05;
        }
    }

    for (int i = 0; i < SAMPLE_NUMBER; i++) {
        double random = rand()%(N+1) / (double)N;
        if (A[i] == true && random < 0.7) {
          w[i] = w[i] * 0.7;
        }
        else if (A[i] == false && random < 0.01) {
          w[i] = w[i] * 0.01;
        }
    }
    int BFalse = 0;
    int BTrue = 0;
    int sample = 0;
    for (int i = 0; i < SAMPLE_NUMBER; i++) {
        if (w[i] == 0.63 || w[i] == 0.0005) {
            sample++;
            if (B[i] == true)
                BTrue++;
            else
                BFalse++;
        }
    }
    for (int i = 0; i < SAMPLE_NUMBER; i++) {
        if ((int)w[i]) {
            den++;
            num = num + w[i] * (BTrue / (double)sample);
        }
    }
    return num/(double)den;
}

int main(void) {
    srand((unsigned)time(NULL));
    cout << "The probability from livelihood weighting is: " << likelihoodWeighting() << endl;
    return 0;
}
