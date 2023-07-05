#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "request.h"
#include "response.h"

int is_directory(char *path) {
    return path[strlen(path) - 1] == '/' ? 1 : 0;
}

void set_mime_type(char path[], char response[]) {
    char *extension = strrchr(path, '.');

    if (extension == NULL) {
        strcat(response, "Content-Type: text/html\n");
    } else if (strcmp(extension, ".css") == 0) {
        strcat(response, "Content-Type: text/css\n");
    } else if (strcmp(extension, ".js") == 0) {
        strcat(response, "Content-Type: text/javascript\n");
    } else if (strcmp(extension, ".png") == 0) {
        strcat(response, "Content-Type: image/png\n");
    } else if (strcmp(extension, ".jpg") == 0) {
        strcat(response, "Content-Type: image/jpg\n");
    } else if (strcmp(extension, ".jpeg") == 0) {
        strcat(response, "Content-Type: image/jpeg\n");
    } else if (strcmp(extension, ".gif") == 0) {
        strcat(response, "Content-Type: image/gif\n");
    } else if (strcmp(extension, ".svg") == 0) {
        strcat(response, "Content-Type: image/svg+xml\n");
    } else if (strcmp(extension, ".ico") == 0) {
        strcat(response, "Content-Type: image/x-icon\n");
    } else if (strcmp(extension, ".json") == 0) {
        strcat(response, "Content-Type: application/json\n");
    } else {
        strcat(response, "Content-Type: text/html\n");
    }
}

void set_http_body(int socket, FILE *file, char response[]) {
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    snprintf(response + strlen(response), 100, "Content-Length: %ld\n\n", fsize);
    send(socket, response, strlen(response), 0);

    char *buffer = malloc(fsize + 1);
    size_t bytesRead;
    
    while ((bytesRead = fread(buffer, 1, fsize, file)) > 0) {
        send(socket, buffer, bytesRead, 0);
    }

    free(buffer);
}

void set_http_status(RESPONSE_STATUS status, char response[]) {
    switch (status) {
        case OK:
            strcat(response, "HTTP/1.1 200 OK\n");
            break;
        case BAD_REQUEST:
            strcat(response, "HTTP/1.1 400 Bad Request\n");
            break;
        case NOT_FOUND:
            strcat(response, "HTTP/1.1 404 Not Found\n");
            break;
        case INTERNAL_SERVER_ERROR:
            strcat(response, "HTTP/1.1 500 Internal Server Error\n");
            break;
        default:
            strcat(response, "HTTP/1.1 500 Internal Server Error\n");
            break;
    }
}

void set_http_header(RESPONSE_STATUS status, char response[], char path[]) {
    set_http_status(status, response);

    if (status == OK) {
        set_mime_type(path, response);
    }
}

void send_file(int socket, char *path) {
    char response[8100] = "";

    if (is_directory(path) == 1) {
        strcat(path, "index.html");
    }
    
    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        set_http_header(NOT_FOUND, response, path);
        strcat(response, "Page not found");
        send(socket, response, strlen(response), 0);
    } else {
        set_http_header(OK, response, path);
        set_http_body(socket, file, response);
    }
    
    fclose(file);
}
