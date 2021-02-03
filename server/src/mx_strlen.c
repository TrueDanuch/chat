#include "server.h"

int mx_strlen(const char *s) 
{
    int i = 0;
    char c = s[0];
    while(c != '\0') {
        i++;
        c = s[i];
    }
    return i;
}
