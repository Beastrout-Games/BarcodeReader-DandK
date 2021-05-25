#include "LightDataReader.h"
#include "Interpreter.h"

#include <stdio.h>

int main(void) {
    size_t sensorCount;
    char *lightData = readLightData(&sensorCount);
    char *binaryData = interpretLightData(lightData, sensorCount);
    free(lightData);

    free(binaryData);

    return 0;
}
