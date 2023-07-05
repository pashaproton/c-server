#ifndef REQUEST_H
#define REQUEST_H

typedef enum {
    GET,
    POST,
    PUT,
    DELETE,
    OPTIONS,
    HEAD,
    CONNECT,
    TRACE,
    PATCH,
    UNKNOWN
} REQUEST_METHOD;

REQUEST_METHOD get_request_method(char buffer[]);
void get_request_path(char buffer[], char path[]);

#endif
