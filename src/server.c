#include "../include/server.h"
int create_socket(void) {
    const int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("Fail to create a socket.");
    }

    struct sockaddr_in addr = {
        .sin_len = 0,
        .sin_family = PF_INET,
        .sin_addr.s_addr = inet_addr(SERVERIP),
        .sin_port = htons(SERVER_PORT)
    };



    close(socket_fd);
    return 0;
}
