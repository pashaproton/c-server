#include <stdlib.h>
#include <string.h>

#include "request.h"

/**
 * @brief Get the request method
 * 
 * @param buffer
 * @return REQUEST_METHOD 
 */
REQUEST_METHOD get_request_method(char buffer[]) {
    if (strstr(buffer, "GET") != NULL) {
        return GET;
    } else if (strstr(buffer, "POST") != NULL) {
        return POST;
    } else if (strstr(buffer, "PUT") != NULL) {
        return PUT;
    } else if (strstr(buffer, "DELETE") != NULL) {
        return DELETE;
    } else if (strstr(buffer, "OPTIONS") != NULL) {
        return OPTIONS;
    } else if (strstr(buffer, "HEAD") != NULL) {
        return HEAD;
    } else if (strstr(buffer, "CONNECT") != NULL) {
        return CONNECT;
    } else if (strstr(buffer, "TRACE") != NULL) {
        return TRACE;
    } else if (strstr(buffer, "PATCH") != NULL) {
        return PATCH;
    } else {
        return UNKNOWN;
    }
}

/**
 * @brief Get the request path
 * 
 * @param buffer
 * @param path
 * @return void
 */
void get_request_path(char buffer[], char path[]) {
    int c = strlen(path);
    int i = 0;

    while (buffer[i] != ' ') {
        i++;
    }

    i++;

    while (buffer[i] != ' ') {
        path[c] = buffer[i];
        c++;
        i++;
    }

    path[c] = '\0';
}
