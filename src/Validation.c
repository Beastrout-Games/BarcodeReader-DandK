#include "Validation.h"

int controlValueC(int n, const int *weights) {
    int C = 0;
    for (int i = 1; i <= n; i++) {
        C += ((n - i) % 10 + 1) * weights[i - 1]; 
    }
    C %= 11;

    return C;
}

int controlValueK(int n, const int *weights) {
    int K = 0;
    for (int i = 1; i <= n + 1; i++) {
        K += ((n - i + 1) % 9 + 1) * weights[i - 1]; 
    }
    K %= 11;
    
    return K;
}
