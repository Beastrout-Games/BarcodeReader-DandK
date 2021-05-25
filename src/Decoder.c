#include "Decoder.h"
#include "Defines.h"
#include "ErrorChecks.h"

#include <string.h>
#include <stdlib.h>

char *barcodeFromBinData(const char *binaryData) {
    char *barcode = (char *) malloc( (strlen(binaryData) / 5) + 1 );
    memAllocationCheck(barcode, __func__);

    char *codes[] = {
        ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, START_STOP
    };

    int startsFound = 0;
    int step = 1;
    for (int i = 0; i < strlen(binaryData); i += step) {
        if (strncmp(START_STOP, &binaryData[i], CODE_LEN) == 0) {
            startsFound++;
            step = CODE_LEN;
        }
    }
    
}
