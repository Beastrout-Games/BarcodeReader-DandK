#include "Decoder.h"
#include "Defines.h"
#include "ErrorChecks.h"
#include "StringUtil.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FULL_BARCODE 2
#define TRUNCATED_BARCODE 1
#define NO_BARCODE 0

static void decodeMeaningfulData(const char *binData, char *barcode);
static char *getMeaningfulSection(char *binData);
static void findStartStopSignals(char *binData, char **start, char **stop);
static int checkBarcode(char **begin, char **end);
static inline size_t getDecodableLen(const char *binaryData);

char *decodeBinData(char *binaryData) {
    char *barcode = (char *) calloc( (strlen(binaryData) / 5) + 1 , sizeof(char));
    memAllocationCheck(barcode, __func__);
    
    char *meaningfulData = getMeaningfulSection(binaryData);
    if (meaningfulData == NULL) {
        return NULL;
    }

    decodeMeaningfulData(meaningfulData, barcode);
    
    return barcode;
}

static char *getMeaningfulSection(char *binData) {
    char *begin, *end;
    
    findStartStopSignals(binData, &begin, &end);

    if (checkBarcode(&begin, &end) == FULL_BARCODE) {
        return begin;
    }

    strrev(binData);

    findStartStopSignals(binData, &begin, &end);

    switch (checkBarcode(&begin, &end)) {
        case FULL_BARCODE:
            return begin;

        case TRUNCATED_BARCODE:
            printf("Barcode truncated. Please center the scanner.\n");
            return NULL;
            
        case NO_BARCODE:
            printf("No barcode found.");
            return NULL;
    }
}

static int checkBarcode(char **begin, char **end) {
    if (*begin && *end) {
        *begin += CODE_LEN;
        **end = '\0';
        return FULL_BARCODE;

    } else if (*begin) {
        return TRUNCATED_BARCODE;
    }

    return NO_BARCODE;
}

static void findStartStopSignals(char *binData, char **start, char **stop) {    
    size_t len = getDecodableLen(binData);
    
    *start = *stop = NULL;

    int step = 1;
    for (int i = 0; i < len; i += step) {
        if (strncmp(START_STOP, &binData[i], CODE_LEN) == 0) {
            if (*start == NULL) {
                *start = &binData[i];
                step = CODE_LEN;
            } else {
                *stop = &binData[i];
                return;
            }
        }
    }
}

static void decodeMeaningfulData(const char *binData, char *barcode) {
    const char *codes[] = {
        ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN };
    
    const char *symbols = SYMBOL_STRING;

    size_t len = getDecodableLen(binData);

    for (int i = 0; i < len; i += CODE_LEN) {
        for (int c = 0; c < strlen(symbols); c++) {
            if (strncmp(&binData[i], codes[c], CODE_LEN) == 0) {
                strappend(barcode, symbols[c]);
                break;
            }
        }
    }
}

static inline size_t getDecodableLen(const char *binaryData) {
    size_t len = strlen(binaryData);
    len -= len % CODE_LEN;

    return len;
}
