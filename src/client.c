#include "../include/server.h"
void error_handle(char* fmt) {
    printf("%s", fmt);
    exit(-1);
}
int main(int argc, char** argv) {
    int             sockfd, n;
    struct sockaddr_in          servaddr;
    char            sendline[MAXLINE];
    char            recvline[MAXLINE];
    if(argc != 2) {
        error_handle("Too few argument!");
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error_handle("Error creating the socket");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);

    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        error_handle("inet_pton error");
    }
    if(connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        error_handle("Connect failed");
    }

    sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
    int sendbytes = strlen(sendline);

    if(write(sockfd, sendline, sendbytes) != sendbytes) {
        error_handle("Write error!");
    }

    while( (n = read(sockfd, recvline, MAXLINE - 1)) > 0) {
        printf("%s", recvline);
        memset(recvline, 0, MAXLINE);
    }
    if(n < 0) {
        error_handle("Read error");
    }


    exit(0);



}