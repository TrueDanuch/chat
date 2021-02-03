#include "server.h"

void Register(char buf[]) {
    char name[16];
    char password[8];
    for (int i = 4; i < 20; ++i) {
        name[i - 4] = buf[i];
    }
    for (int i = 20; i < 8; ++i) {
        password[i - 20] = buf[i];
    }

}

void MessageDelete(int fd, char buf[]) {
    char sender[9];
    char reciever[9];

    for (int i = 4; i < 12; i++) {
        sender[i - 4] = buf[i];
    }
    
    for (int i = 12; i < 20; i++) {
        reciever[i - 12] = buf[i];
    }
    sender[8] = '\0';
    reciever[8] = '\0';

    printf("Sender: %s\n\n", sender);
    printf("Reciever: %s\n\n", reciever);
    write(fd, sender, strlen(sender));
}

void Quit(int fd, int I) {
    close( fd );   
    client_socket[I] = 0; 
}

void SendMessage(char buf[]) {
    /*
    char id[4];
    for (int i = 5; i < 8; i++) {
        id[i - 5] = buf[i];
    } 
    */
    int len = strlen(buf);
    char text[len - 5];

    for (int i = 5; i < len; i++) {
        text[i - 5] = buf[i];
    }
    char chid[1];
    chid[0] = buf[4];
    int id = atoi(chid);
    write(id, text, strlen(text));

}

void Decrypt(char buf[], int fd, int I) {
    
    char fst_word[4];
    for(int i = 0; i < 4; ++i) {
        fst_word[i] = buf[i];
    }

    printf("First word: %s\n", fst_word);

    if (!strncmp(fst_word, "quit", 4))  {
        write(fd, "Disconnect\n", strlen("Disconnect\n"));
        Quit(fd, I);
    }
    else if (!strncmp(fst_word, "mesg", 4)) {
        SendMessage(buf);
    }
    else if (!strncmp(fst_word, "msed", 4)) {
        //MessageEdit(fd, buf);
        ;
    }
    else if (!strncmp(fst_word, "msdl", 4)) {
        MessageDelete(fd, buf);
    }else
        write(fd, buf, strlen(buf));

    
}
