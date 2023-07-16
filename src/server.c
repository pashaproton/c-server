#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "config.h"
#include "request.h"
#include "response.h"

int main(int argc, char *argv[]) {
    int server_fd,  // socket file descriptor
        new_socket, // new socket file descriptor
        valread;    // number of bytes read

    struct Config config = parse_args(argc, argv);

    struct sockaddr_in address;

    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(config.port);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    char buffer[1024] = {0};

    printf("Listening on port %d\n", config.port);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        valread = recv(new_socket, buffer, 1024, 0);

        if (valread == 0) {
            printf("No data received\n");
        } else if (valread == -1) {
            printf("Client disconnected\n");
            exit(EXIT_FAILURE);
        }

        char path[1024] = "";
        strcpy(path, config.root);
        get_request_path(buffer, path);
        send_file(new_socket, path);
        close(new_socket);
    }

    shutdown(server_fd, SHUT_RDWR);

    return 0;
}
