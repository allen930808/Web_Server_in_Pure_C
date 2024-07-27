#include "../include/server.h"
int main(void) {
    struct addrinfo hint, *res;
    struct sockaddr_storage client_addr;
    socklen_t addr_size = sizeof(client_addr);
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, PORT, &hint, &res);
    const int socketfd = socket(res -> ai_family, res -> ai_socktype, res -> ai_protocol);
    bind(socketfd, res -> ai_addr, res -> ai_addrlen);
    listen(socketfd, BACKLOG);
    int new_fd = accept(socketfd, (struct sockaddr* )&client_addr, &addr_size);
    char* msg = "hi there";
    int len = strlen(msg);
    int byte_sent;
    byte_sent = send (new_fd, msg,len, 0 );

}
