
#include "../include/server.h"
void main(void) {
    int s = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {
        0,
        AF_INET,
        0x901f
    };
    bind(s, &addr, sizeof(addr));

    listen(s, 10);

    int clinet_fd = accept(s, 0, 0);
    char buffer[256] = {0};
    recv(clinet_fd, buffer, 256, 0);
    char* f = buffer + 5;
    *strchr(f,' ') = 0;
    int opened_fd = open(f, O_RDONLY);
    sendfile(clinet_fd, opened_fd, 0, 256);
    close(opened_fd);
    close(clinet_fd);
}
