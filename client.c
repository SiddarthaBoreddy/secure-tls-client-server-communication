#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <limits.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#define HOSTNAME "localhost"

int InitSocket(char *hostname, int port) {
    int sd;
    struct hostent *host;
    struct sockaddr_in addr;

    if ((host = gethostbyname(hostname)) == NULL) {
        perror("Error resolving hostname");
        exit(EXIT_FAILURE);
    }

    sd = socket(PF_INET, SOCK_STREAM, 0);
    if (sd == -1) {
        perror("Cannot create socket");
        exit(EXIT_FAILURE);
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);

    if (connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        perror("Connect failed");
        close(sd);
        exit(EXIT_FAILURE);
    }
    return sd;
}

void Process(int sd) {
    char buffer[21];
    char num[20];

    while (1) {
        printf("Input a number: ");
        if (fgets(num, sizeof(num), stdin) == NULL) {
            if (feof(stdin)) {  // Check for EOF
                printf("\nEOF received. Exiting...\n");
                break;  // Exit loop on EOF
            } else {
                perror("Error reading input");
                break;
            }
        }

        // Remove newline character, if any
        num[strcspn(num, "\n")] = 0;

        // exit to leave
        if (strcmp(num, "exit") == 0) {
            break;
        }

        if (strlen(num) == 0) {
            continue;  // Ignore empty input and continue
        }
        char* endptr;
        long long val = strtoll(num, &endptr, 10);
        if (endptr == num || *endptr != '\0') {
            printf("Invalid input: '%s' is not a number.\n", num);
            continue;  
        }
        if (val > INT_MAX || val < INT_MIN) {
            printf("Number out of range: '%s' is not a 32-bit integer.\n", num);
            continue;  
        }

        if (send(sd, num, strlen(num), 0) < 0) {
            perror("Send failed");
            break;
        }

        int bytes = recv(sd, buffer, sizeof(buffer)-1, 0);
        if (bytes < 0) {
            perror("Receive failed");
            break;
        } else if (bytes == 0) {
            printf("Server closed the connection\n");
            break;
        }

        buffer[bytes] = '\0';
        printf("Received from server: %s\n", buffer);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    int sd = InitSocket(HOSTNAME, port);

    Process(sd);

    close(sd);
    return 0;
}

