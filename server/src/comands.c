#include "server.h"

void SearchUserComand(char buf[], int fd) {
    char username[16];
    bzero(username, 16);

    printf("fst\n");
    for (int i = 4; i < 20; i++) {
        username[i - 4] = buf[i];
    }
    printf("snd\n");
    if (SearchUser(addX(username))) {
        write(fd, "sury\r", 5);
    }else   
        write(fd, "surf\r", 5);
}

void UpdateMesgComand(char buf[], int fd) {
    char chatName[33];
    char id[4];

    bzero(chatName, 33);
    bzero(id, 4);

    for (int i = 4; i < 36; i++) {
        chatName[i - 4] = buf[i];
    }
    for (int i = 36; i < 40; i++) {
        id[i - 36] = buf[i];
    }
    UpdateMessages(chatName, id, fd);
}

void UpdateChatsComand(char buf[], int fd) {
    char username[17];
    bzero(username, 16);

    for (int i = 4; i < 20; i++) {
        username[i - 4] = buf[i];
    }
    addX(username);
    UpdateChats(username, fd);
}

void NewChatComand(char buf[], int fd) {
    char name1[17];
    char name2[17];
    char chatName[33];

    for (int i = 4; i < 20; ++i) {
        name1[i - 4] = buf[i];
        chatName[i - 4] = buf[i];
    }
    name1[16] = '\0';
    for (int i = 20; i < 36; ++i) {
        name2[i - 20] = buf[i];
        chatName[i - 4] = buf[i];
    }
    name2[16] = '\0';

    NewChat(name1, name2);
    buf[strlen(buf)] = '\r';
    char reciever[17];
    bzero(reciever, 17);
    for(int i = 0; i < 2; i++) {
        for (int k = 0; k < 16; k++) {
            reciever[k] = chatName[k + 16 * i];
        }

        for (unsigned int i = 0; i < (sizeof(signedInUser) / sizeof(*signedInUser)); i++) {
            if (!(strncmp(reciever, signedInUser[i], 16))) {
                write(client_socket[i], buf, strlen(buf));
                break;
            }
        }
    }

    fd = 0;
}

void SignIn(char buf[], int fd, int I) {
    char name[17];
    char password[9];
    for (int i = 4; i < 20; ++i) {
        name[i - 4] = buf[i];
    }
    name[16] = '\0';
    for (int i = 20; i < 28; ++i) {
        password[i - 20] = buf[i];
    }
    password[8] = '\0';
    fprintf(stdout, "Name: %s PASSWORD: %s\n", name, password);

    if (GetUser(name, password)) {
        strncat(signedInUser[I], name, 17);
        write (fd, "siny\r", 5);
    }
    else
        write(fd, "sinf\r", 5);

    printf("users:\n");
    for (unsigned int i = 0; i < (sizeof(signedInUser) / sizeof(*signedInUser)); i++) {
        printf("%d: %s\n", i, signedInUser[i]);
    }
}

void SignUp(char buf[], int fd) {
    char name[17];
    char password[9];

    for (int i = 4; i < 20; ++i) {
        name[i - 4] = buf[i];
    }
    name[16] = '\0';
    for (int i = 20; i < 28; ++i) {
        password[i - 20] = buf[i];
    }
    password[8] = '\0';

    fprintf(stdout, "Name: %s PASSWORD: %s\n", name, password);
    if (InsertUser(name, password)) 
        write(fd, "supy\r", 5);
    else
        write(fd, "supf\r", 5);
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
    bzero(signedInUser[I], 17);
}

void SendMessageToBoth(char chatName[32], char text[], int ID) {
    int len = strlen(text) + 4 + 32;
    char mesg[len + 14];
    char reciever[17];
    char id[5];
    bzero(id, 5);
    if (ID == -1)
        strcat(id, addzr(NewMesageID(chatName)));
    else {
        strcat(id, addzr(ID));
    }

    bzero(reciever, 17);
    bzero(mesg, len + 10);
    strcat(mesg, "mesg");
    strncat(mesg, chatName, 32);
    strncat(mesg, id, 4);
    strncat(mesg, text, strlen(text));

    for(int i = 0; i < 2; i++) {
        for (int k = 0; k < 16; k++) {
            reciever[k] = chatName[k + 16 * i];
        }

        for (unsigned int i = 0; i < (sizeof(signedInUser) / sizeof(*signedInUser)); i++) {
            if (!(strncmp(reciever, signedInUser[i], 16))) {
                mesg[strlen(mesg)] = '\r';
                write(client_socket[i], mesg, strlen(mesg));
                break;
            }
        }
    }
}

void SendMessage(char buf[]) {
    char chatName[33];    
    int len = strlen(buf);
    char text[len - 35];
    for (int i = 4; i < 36; i++) {
        chatName[i - 4] = buf[i];
    }
    chatName[32] = '\0';

    for (int i = 36; i < len; i++) {
        text[i - 36] = buf[i];
    }
    text[len - 36] = '\0';

    NewMesage(chatName, text);
    
    SendMessageToBoth(chatName, text, -1);
}

void Decrypt(char buf[], int fd, int I) {
    
    char fst_word[4];
    for(int i = 0; i < 4; ++i) {
        fst_word[i] = buf[i];
    }

    printf("First word: %s\n", fst_word);

    if (!strncmp(fst_word, "quit", 4))  {
        Quit(fd, I);
    }
    else if (!strncmp(fst_word, "mesg", 4)) {
        SendMessage(buf);
    }
    else if (!strncmp(fst_word, "msed", 4)) {
        ;
    }
    else if (!strncmp(fst_word, "msdl", 4)) {
        MessageDelete(fd, buf);
    }else if (!strncmp(fst_word, "sgup", 4)) {
        SignUp(buf, fd);
    }else if (!strncmp(fst_word, "sgin", 4)) {
        SignIn(buf, fd, I);
    }else if (!strncmp(fst_word, "nwch", 4)) {
        NewChatComand(buf, fd);
    }else if (!strncmp(fst_word, "updc", 4)) {
        UpdateChatsComand(buf, fd);
    }else if (!strncmp(fst_word, "updm", 4)) {
        UpdateMesgComand(buf, fd);
    }else if (!strncmp(fst_word, "srur", 4)) {
        SearchUserComand(buf, fd);
    }else
        write(fd, buf, strlen(buf));

    
}
