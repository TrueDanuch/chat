#include "client.h"

int main(int adc, char* adv[]) {
    adc = 1;

    int fd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in adr;
    adr.sin_family = AF_INET;
    adr.sin_port = htons(atoi(adv[2]));

    adr.sin_addr.s_addr = inet_addr(adv[1]);

    Connect(fd, (struct sockaddr *) &adr, sizeof adr);

    write(fd, "Hello\n", 6);

    char buf[256];
    recv(fd, &buf, sizeof(buf), 0);

    printf("Server: %s",buf);

    sleep(1);
    close(fd);
    return 0;
}
