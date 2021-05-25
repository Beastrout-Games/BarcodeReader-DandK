#include "LightDataReader.h"
#include "Defines.h"
#include "ErrorChecks.h"

#include <stdio.h>
#include <stdlib.h>

static void resolveUncertain(int count, char *from, char value);
static char *binarizeLightData(size_t sensorCount, const float *data);

char *readLightData(size_t *sensorCount) {
    int scanReturn = scanf("%lu", sensorCount);
    inputCheck(scanReturn, 1, __func__);

    float *data = (float *) malloc(sizeof(float) * (*sensorCount));
    memAllocationCheck(data, __func__);

    for (int i = 0; i < *sensorCount; i++) {
        int scanReturn = scanf(" %f", &data[i]);
        inputCheck(scanReturn, 1, __func__);
    }

    char *binData = binarizeLightData(*sensorCount, data);
    free(data);

    return binData;
}

static char *binarizeLightData(size_t sensorCount, const float *data) {
    char *binData = (char *) malloc(sensorCount + 1);
    memAllocationCheck(binData, __func__);

    int uncertainDataCount = 0;
    for (int i = 0; i < sensorCount; i++) {

        if (data[i] > UPPER_MARGIN) {
            binData[i] = '1';
            resolveUncertain(uncertainDataCount, &binData[i-1], '0');
            uncertainDataCount = 0;

        } else if (data[i] < LOWER_MARGIN) {
            binData[i] = '0';
            resolveUncertain(uncertainDataCount, &binData[i-1], '1');
            uncertainDataCount = 0;

        } else {
            uncertainDataCount++;
            binData[i] = ERROR_SYMBOL;
        }
    }

    binData[sensorCount] = '\0';

    if (uncertainDataCount > 0) {
        resolveUncertain(uncertainDataCount, &binData[sensorCount - 1], '1');
    }

    return binData;
}

static void resolveUncertain(int count, char *from, char value) {
    while (count--) {
        *from = value;
        from--;
    }
}
