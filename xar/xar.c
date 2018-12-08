#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *cmd = malloc(sizeof(char *));

    for (int i = 1; i < argc; ++i) {
        strcat(cmd, argv[i]);
        strcat(cmd, " ");
    }

    char data[BUFSIZ];
    ssize_t read_bytes = 0;
    while ((read_bytes = read(STDIN_FILENO, data, BUFSIZ)) > 0) {
        strcat(cmd, data);
    }

    system(cmd);
}
