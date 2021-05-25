#ifndef ERROR_CHECKS_H
#define ERROR_CHECKS_H

void memAllocationCheck(const void *ptr, const char *funcName);
void inputCheck(int scanRet, int expected, const char *funcName);

#endif /* ERROR_CHECKS_H */
