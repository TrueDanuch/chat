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
    fprintf(stdout, "START\n");
    int len = strlen(buf);
    char chatName[33];
    char text[len - 36];
    char msID;
    fprintf(stdout, "created variables\n");
    msID = buf[36];
    printf("ID\n");
    for (int i = 4; i < 36; i++) {
        chatName[i - 4] = buf[i];
    }
    chatName[32] = '\0';
    fprintf(stdout, "Chatname\n");
    for (int i = 37; i < len-1; i++) {
        text[i - 37] = buf[i];
    }
    text[len - 37] = '\0';
    fprintf(stdout, "text: %s!!!\n", text);

    MesageRecieve(msID, chatName, text);

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
    }
    else if (!strncmp(fst_word, "msdl", 4)) {
        MessageDelete(fd, buf);
    }
    
}
