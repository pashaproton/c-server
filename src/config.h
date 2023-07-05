#ifndef CONFIG_H
#define CONFIG_H

struct Config {
    int port;
    char root[256];
};

struct Config parse_args(int argc, char *argv[]);

#endif
