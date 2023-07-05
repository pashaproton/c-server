#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"

struct Config parse_args(int argc, char *argv[]) {
    struct Config config;

    config.port = 8080;
    strcpy(config.root, argv[1] ? argv[1] : ".");

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {
            config.port = atoi(argv[i + 1]);
        }
    }

    return config;
}
