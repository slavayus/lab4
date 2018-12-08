#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *cmd = malloc(sizeof(char *));

    for (int i = 1; i < argc - 1; ++i) {
        strcat(cmd, argv[i]);
        strcat(cmd, " ");
    }
    strcat(cmd, argv[argc - 1]);

    char data[BUFSIZ];
    ssize_t read_bytes = 0;
    size_t cmd_size = BUFSIZ;
    char *cmd_args = malloc(cmd_size);
    while ((read_bytes = read(STDIN_FILENO, data, BUFSIZ - 1)) > 0) {
        strcat(data, "\0");
        if (cmd_size > strlen(cmd_args) + strlen(data)) {
            strcat(cmd_args, data);
        } else {
            cmd_size += BUFSIZ;
            char *new_args = malloc(cmd_size);
            strcpy(new_args, cmd_args);
            strcat(new_args, data);
            cmd_args = new_args;
        }
    }

    execlp(cmd, cmd, cmd_args, NULL);
}
