#include "Validation.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>

static int controlValueC(int n, const int *weights);
static int controlValueK(int n, const int *weights);

bool validate(char *decodedSymbols) {
    size_t len = strlen(decodedSymbols);

    int weights[len];
    for (int i = 0; i < len; i++) {
        if (decodedSymbols[i] == '-') {
            weights[i] = 10;
        } else {
            weights[i] = (int) decodedSymbols[i] - '0';
        }
    }

    bool validC = (controlValueC(len - 2, weights) == weights[len - 2]);
    bool validK = (controlValueK(len - 2, weights) == weights[len - 1]);

    if (validC && validK) {
        decodedSymbols[len - 2] = '\0';
        return true;

    } else {
        decodedSymbols[len - 2] = '\0';
        return false;
    }
}

static int controlValueC(int n, const int *weights) {
    int C = 0;
    for (int i = 1; i <= n; i++) {
        C += ((n - i) % 10 + 1) * weights[i - 1]; 
    }
    C %= 11;

    return C;
}


static int controlValueK(int n, const int *weights) {
    int K = 0;
    for (int i = 1; i <= n + 1; i++) {
        K += ((n - i + 1) % 9 + 1) * weights[i - 1]; 
    }
    K %= 11;
    
    return K;
}
