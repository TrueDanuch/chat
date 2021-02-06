#include "client.h"

void NewChatComand(char chatname[32]) {
    char str[37] = "nwch";
    strcat(str, chatname);

    write(fd, str, strlen(str));
}

void SendMesage(char chatName[32], char* text) {
    char mesg[1054];
    bzero(mesg, 1054);
    strcat(mesg, "mesg");
    strncat(mesg, chatName, 32);
    strcat(mesg, logname);
    strcat(mesg, "\n");
    strncat(mesg, text, strlen(text));
    mesg[strlen(mesg)] = '\0';

    write(fd, mesg, strlen(mesg));
}

/*
void MessageEdit(int fd, char buf[]) {

}
*/

void MessageDelete(int fd, char buf[]) {
    char sender[8];
    for (int i = 4; i < 12; i++) {
        sender[i - 4] = buf[i];
    }
    printf("Sender: %s", sender);
    write(fd, sender, strlen(sender));
}

void Quit(int fd) {
    close( fd );
}

void MessageRecieveComand(char buf[]) {
    int len = strlen(buf);
    char chatName[33];
    char text[len - 40];
    char msID[5];

    for (int i = 4; i < 36; i++) {
        chatName[i - 4] = buf[i];
    }
    chatName[32] = '\0';
    addX(chatName);

    for (int i = 36; i < 40; i++) {
        msID[i - 36] = buf[i];
    }
    msID[4] = '\0';

    for (int i = 40; i < len-1; i++) {
        text[i - 40] = buf[i];
    }
    text[len - 41] = '\0';

    MesageRecieve(msID, chatName, text);
}

void NewChatReciveComand(char buf[]) {
    char chatName[33];
    for (int i = 4; i < 36; i++) {
        chatName[i - 4] = buf[i];
    }
    chatName[32] = '\0';
    addX(chatName);

    NewChat(chatName);

}

void Decrypt(char buf[], int fd) {
    
    char fst_word[4];
    for(int i = 0; i < 4; ++i) {
        fst_word[i] = buf[i];
    }

    printf("First word: %s\n", fst_word);

    if (!strncmp(fst_word, "quit", 4))  {
        write(fd, "Disconnect\n", strlen("Disconnect\n"));
        Quit(fd);
    }
    else if (!strncmp(fst_word, "mesg", 4)) {
        MessageRecieveComand(buf);
    }
    else if (!strncmp(fst_word, "msed", 4)) {
        //MessageEdit(fd, buf);
        ;
    }else if (!strncmp(fst_word, "nwch", 4)) {
        NewChatReciveComand(buf);
    }else if (!strncmp(fst_word, "siny", 4)) {
        sginInt = 1;
    }else if (!strncmp(fst_word, "sinf", 4)) {
        sginInt = 0;
    }
    else if (!strncmp(fst_word, "msdl", 4)) {
        MessageDelete(fd, buf);
    }
    
}
