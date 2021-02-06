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

void SGUP(char* login, char* password) {
    char mesg[29];
    AddSpace(login);
    bzero(mesg, 29);
    strcat(mesg, "sgup");
    strncat(mesg, login, 16);
    strncat(mesg, password, 8);
    write(fd, mesg, strlen(mesg));
}
