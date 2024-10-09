#include <stdbool.h>
#include <string.h>
bool trim_newline(char *s){
    if (!s) return false;
    int length = strlen(s);
    if (length <= 0) return false;
    *(s+length-1) = '\0';
    return true;
}