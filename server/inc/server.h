#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <stdio.h>  
#include <string.h>   //strlen  
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>   //close  
#include <arpa/inet.h>    //close  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdbool.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <sqlite3.h>

#define TRUE   1  
#define FALSE  0

int client_socket[30];
struct sockaddr_in address;  

void mx_str_reverse(char *s);
char *mx_strcpy(char *dst, const char *src);
char *mx_itoa(int number);
int number_length(int number);
char *mx_strnew(const int size);
void mx_swap_char(char *s1, char *s2);
int mx_strlen(const char *s);

void read_file(char* buf);

int mx_atoi(const char *str);

bool mx_isdigit(int c);

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Inet_pton(int af, const char *src, void *dst);

void Decrypt(char buf[], int fd, int I);

int DataBase();

#endif
