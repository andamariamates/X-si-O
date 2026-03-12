#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

void* recv_thread(void* arg) {
    int client_sock = *(int*)arg;
    char buffer[1024];

    while (1) {
        int bytes = recv(client_sock, buffer, sizeof(buffer)-1, 0);
        if (bytes <= 0) {
            printf("Clientul s-a deconectat.\n");
            exit(0);
        }
        buffer[bytes] = '\0';
        printf("\n[Client]: %s", buffer);
        fflush(stdout);
    }
    return NULL;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_sock, 1);

    printf("Server pornit. Astept client...\n");

    int client_sock = accept(server_sock, NULL, NULL);
    printf("Client conectat!\n");

    pthread_t thread;
    pthread_create(&thread, NULL, recv_thread, &client_sock);

    char text[1024];
    while (1) {
        fgets(text, sizeof(text), stdin);
        send(client_sock, text, strlen(text), 0);
    }

    close(client_sock);
    close(server_sock);
    return 0;
}