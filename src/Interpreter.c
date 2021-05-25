#include "Interpreter.h"
#include "ErrorChecks.h"
#include "Defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool writeInterpretedBit(char *interpretedData, int *interpretedCount, int *darkBits);

char *interpretLightData(const char *lightData, size_t sensorCount) {
    char *interpretedData = (char *) malloc((sensorCount / 2) + 1);
    memAllocationCheck(interpretedData, __func__);

    int dark = 0, interpretedCount = 0;

    for (int i = 0; i < sensorCount; i++) {
        
        if (lightData[i] == '0') {
            dark++;

        } else if (lightData[i] == '1') {
            bool end = writeInterpretedBit(interpretedData, &interpretedCount, &dark);
            
            if (end) {
                if (interpretedCount > CODE_LEN) {
                    break;
                }
                interpretedCount = 0;
            }
        }

        else {
            fprintf(stderr, "Error in %s: Corrupted binary sensor data.\n", __func__);
        }
    }

    interpretedData[interpretedCount] = '\0';
    
    return interpretedData;
}

static bool writeInterpretedBit(char *interpretedData, int *interpretedCount, int *darkBits) {
    if (*darkBits == 1) {
        interpretedData[*interpretedCount] = '0';
        *darkBits = 0;
        (*interpretedCount)++;
        return false;

    } else if (*darkBits == 2) {
        interpretedData[*interpretedCount] = '1';
        *darkBits = 0;
        (*interpretedCount)++;
        return false;
    
    } else {
        return true;
    }
}

