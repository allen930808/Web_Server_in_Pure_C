#include "../include/server.h"

void start_server(void) {
    struct addrinfo hint, *res;
    struct sockaddr_storage client_addr;
    socklen_t addr_size = sizeof(client_addr);
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    int status;
    if ((status = getaddrinfo(NULL, PORT, &hint, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    int socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (socketfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socketfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    if (listen(socketfd, BACKLOG) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %s\n", PORT);

    while (1) {
        int new_fd = accept(socketfd, (struct sockaddr *)&client_addr, &addr_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        char *msg = "hi there";
        int len = strlen(msg);
        if (send(new_fd, msg, len, 0) == -1) {
            perror("send");
        }

        close(new_fd);
    }

    close(socketfd);
}

void start_client(const char *hostname) {
    struct addrinfo hints, *res, *p;
    int sockfd;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(hostname, PORT, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    for (p = res; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("connect");
            close(sockfd);
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    char buf[MAXLINE];
    int numbytes;
    if ((numbytes = recv(sockfd, buf, MAXLINE - 1, 0)) == -1) {
        perror("recv");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buf[numbytes] = '\0';
    printf("client: received '%s'\n", buf);

    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <mode> [hostname]\n", argv[0]);
        fprintf(stderr, "mode: server | client\n");
        return 1;
    }

    if (strcmp(argv[1], "server") == 0) {
        start_server();
    } else if (strcmp(argv[1], "client") == 0) {
        if (argc != 3) {
            fprintf(stderr, "usage: %s client <hostname>\n", argv[0]);
            return 1;
        }
        start_client(argv[2]);
    } else {
        fprintf(stderr, "invalid mode: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
