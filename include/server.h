//
// Created by 陳侑廷 on 2024/7/25.
//

#ifndef SERVER_H
#define SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#define PORT "8080"
#define MAXLINE 2056
#define BACKLOG 10
#define SERVERIP "127.0.0.1"
void start_server(void);
void start_client(const char *hostname);
#endif //SERVER_H
