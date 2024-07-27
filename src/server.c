#include "../include/server.h"
int main(void) {
    struct addrinfo hints, *res;
    struct sockaddr_storage client_addr;
    socklen_t addr_size = sizeof(client_addr);
    int socketfd, new_fd;
    char *msg = "hi there";
    int len = strlen(msg);
    int byte_sent;

    // Setup the hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Get address information
    if (getaddrinfo(NULL, PORT, &hints, &res) != 0) {
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    // Create socket
    socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (socketfd == -1) {
        perror("socket");
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    // Bind socket
    if (bind(socketfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        close(socketfd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res); // Free the address information

    // Listen for connections
    if (listen(socketfd, BACKLOG) == -1) {
        perror("listen");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    // Accept connection
    new_fd = accept(socketfd, (struct sockaddr *)&client_addr, &addr_size);
    if (new_fd == -1) {
        perror("accept");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    // Send message
    byte_sent = send(new_fd, msg, len, 0);
    if (byte_sent == -1) {
        perror("send");
        close(new_fd);
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    // Close sockets
    close(new_fd);
    close(socketfd);

    return 0;
}
