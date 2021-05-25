#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void memAllocationCheck(void *ptr, const char *funcName) {
    if (ptr == NULL) {
        fprintf(stderr, "Error in %s: %s\n", funcName, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void inputCheck(int scanRet, int expected, const char *funcName) {
    if (scanRet != expected) {
        fprintf(stderr, "Error in %s: Invalid input in scanf()\n", funcName);
        exit(EXIT_FAILURE);
    }
}