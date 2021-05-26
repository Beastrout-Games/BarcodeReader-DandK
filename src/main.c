#include "LightDataReader.h"
#include "Interpreter.h"
#include "Decoder.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t sensorCount;
    char *lightData = readLightData(&sensorCount);
    char *binaryData = interpretLightData(lightData, sensorCount);
    free(lightData);

    char *decoded = decodeBinData(binaryData);
    free(binaryData);

    if (decoded == NULL) {
        printf("DEBUG: Bad barcode\n");
        return -1;
    }

    printf("%s\n", decoded);

    free(decoded);

    return 0;
}
