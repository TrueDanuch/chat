#include "client.h"

void SGIN(char* login, char* password) {
    char mesg[29];
    AddSpace(login);
    bzero(mesg, 29);
    strcat(mesg, "sgin");
    strncat(mesg, login, 16);
    strncat(mesg, password, 8);
    write(fd, mesg, strlen(mesg));
}

int SGUP(char* login, char* password, char* password2) {
    char mesg[29];
    if (strcmp(password, password2))
        return 1;

    for(unsigned int i = 0; i < strlen(login); i++) {
        if (!isalpha(login[i])) {
            if (!isdigit(login[i])) {
                return 2;
            }
        }
    }

    AddSpace(login);
    bzero(mesg, 29);
    strcat(mesg, "sgup");
    strncat(mesg, login, 16);
    strncat(mesg, password, 8);
    write(fd, mesg, strlen(mesg));

    return 0;
}
