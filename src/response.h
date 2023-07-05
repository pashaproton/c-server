#ifndef RESPONSE_H
#define RESPONSE_H

typedef enum {
    OK = 200,
    BAD_REQUEST = 400,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500
} RESPONSE_STATUS;

void send_file(int socket, char *path);

#endif
