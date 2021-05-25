#include "Interpreter.h"
#include "ErrorChecks.h"
#include "Defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool writeInterpretedBit(char *meaningfulBits, int *position, int *darkBits);

char *interpretLightData(const char *lightData, size_t sensorCount) {
    char *interpreted = (char *) malloc(sensorCount / 2);
    memAllocationCheck(interpreted, __func__);

    int dark = 0, errors = 0, position = 0;

    for (int i = 0; i < sensorCount; i++) {
        if (lightData[i] == '0') {
            dark++;
        }

        else if (lightData[i] == '1') {
            bool end = writeInterpretedBit(interpreted, &position, &dark);
            
            if (end) {
                if (position > CODE_LEN) {
                    break;
                }
                position = 0;
            }
        }

        else {
            fprintf(stderr, "Error in %s: Corrupted binary sensor data.\n", __func__);
        }
    }

    interpreted[position] = '\0';
    
    return interpreted;
}

static bool writeInterpretedBit(char *interpreted, int *position, int *darkBits) {
    if (*darkBits == 1) {
        interpreted[*position] = '0';
        *darkBits = 0;
        (*position)++;
        return false;
    }
    
    else if (*darkBits == 2) {
        interpreted[*position] = '1';
        *darkBits = 0;
        (*position)++;
        return false;
    }
    
    else {
        return true;
    }
}

