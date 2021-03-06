#include "client.h"

void Socket(int domain, int type, int protocol) {
    fd = socket(domain, type, protocol);
    printf("Creating socket:");
    if (fd == -1) {
        perror(" failed");
        exit(EXIT_FAILURE);
    }

    printf(" successfully\n");
}

void Inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    printf("Inet_pton:");
    if (res == 0) {
        printf(" failed: src does not contain a character"
            " string representing a valid network address in the specified"
            " address family\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        perror(" failed");
        exit(EXIT_FAILURE);
    }
    printf (" successfully\n");
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    printf("Connecting:");
    if (res == -1) {
        perror(" CONNECTION failed");
        //exit(EXIT_FAILURE);
        return 0;
    }

    printf (" successfully\n\n");
    return 1;
}
