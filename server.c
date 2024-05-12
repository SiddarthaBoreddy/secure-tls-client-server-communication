#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

int InitSocket(int port) {
    int sd;
    struct sockaddr_in addr;

    sd = socket(PF_INET, SOCK_STREAM, 0);
    if (sd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        perror("Bind failed");
        close(sd);
        exit(EXIT_FAILURE);
    }

    if (listen(sd, 10) != 0) {
        perror("Listen failed");
        close(sd);
        exit(EXIT_FAILURE);
    }

    return sd;
}

void Process(int client_sd) {
    char buffer[1024];
    int num;

    while (1) {
        int bytes = recv(client_sd, buffer, sizeof(buffer) - 1, 0);
        if (bytes < 0) {
            perror("Receive failed");
            break;
        } else if (bytes == 0) {
            printf("Client closed the connection\n");
            break;
        }

        buffer[bytes] = '\0';
        printf("Received: %s\n", buffer);
        num = atoi(buffer);
        num++;

        sprintf(buffer, "%d", num);
        if (send(client_sd, buffer, strlen(buffer), 0) < 0) {
            perror("Send failed");
            break;
        }
    }

    close(client_sd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    int server_sd = InitSocket(port);

    printf("Listening on port %d\n", port);

    while (1) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        int client_sd = accept(server_sd, (struct sockaddr *)&addr, &len);

        if (client_sd < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Connection from %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        Process(client_sd);
    }

    close(server_sd);
    return 0;
}

