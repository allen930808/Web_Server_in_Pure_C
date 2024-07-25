#include "../include/server.h"
int create_socket(void) {
    int socket_fd;

    if ( ( socket_fd = socket(PF_INET, SOCK_STREAM, 0) ) < 0) {
        perror("Fail to create a socket.");
        return -1;
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

int main() {
    if(create_socket() < 0) {
        exit(-1);
    }

}

