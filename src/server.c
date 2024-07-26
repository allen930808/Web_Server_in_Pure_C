#include "../include/server.h"
int main(void) {
    int status;
    struct addrinfo hint;
    struct addrinfo *serverinfo;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;
    if((status = getaddrinfo(NULL, SERVER_PORT, &hint, &serverinfo)) != 0) {
        perror("getaddrinfo error");
        exit(-1);
    }
    freeaddrinfo(serverinfo);
    return 0;
}
