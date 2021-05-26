#include "LightDataReader.h"
#include "Interpreter.h"
#include "Decoder.h"
#include "Validation.h"

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
        exit(EXIT_FAILURE);
    }

    if (validate(decoded)) {
        printf("%s\n", decoded);
    } else {
        printf("Read invalid barcode %s\n", decoded);
    }

    free(decoded);

    return 0;
}
