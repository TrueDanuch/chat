#include "client.h"

void AddSpace(char *name)
{
    
    for(int i = strlen(name); i < 16; i++)
    {
        name[i] = ' ';
    }
}

char* addX(char* name) {
    for (unsigned int i = 0; i < strlen(name); i++) {
        if (name[i] == ' ') {
            name[i] = '_';
        }
    }
    return name;
}
