#include <stddef.h>
#include <string.h>

char *strrev(char *string) {
    size_t len = strlen(string);
    for (int i = 0; i < len / 2; i++) {
        #define left string[i]
        #define right string[len - i - 1]
        
        left += right;
        right = left - right;
        left -= right;
    }
    
    return string;
}

char *strappend(char *string, char c) {
    size_t len = strlen(string);
    string[len] = c;
    string[len + 1] = '\0';
    return string;
}
