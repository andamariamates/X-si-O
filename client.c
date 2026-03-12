#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

void* recv_thread(void* arg) {
    int sock = *(int*)arg;
    char buffer[1024];

    while (1) {
        int bytes = recv(sock, buffer, sizeof(buffer)-1, 0);
        if (bytes <= 0) {
            printf("Serverul s-a deconectat.\n");
            exit(0);
        }
        buffer[bytes] = '\0';
        printf("\n[Server]: %s", buffer);
        fflush(stdout);
    }
    return NULL;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        return 1;
    }

    printf("Conectat la server!\n");

    pthread_t thread;
    pthread_create(&thread, NULL, recv_thread, &sock);

    char text[1024];
    while (1) {
        fgets(text, sizeof(text), stdin);
        send(sock, text, strlen(text), 0);
    }

    close(sock);
    return 0;
}