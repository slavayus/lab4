#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *arg[argc];
    for (int i = 1; i < argc; ++i) {
        arg[i - 1] = argv[i];
    }

    char data[BUFSIZ];
    ssize_t read_bytes = 0;
    size_t cmd_size = BUFSIZ;
    char *cmd_args = malloc(cmd_size);
    while ((read_bytes = read(STDIN_FILENO, data, BUFSIZ)) > 0) {
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

    cmd_args[strlen(cmd_args) - 1] = '\0';

    arg[argc - 1] = cmd_args;
    arg[argc] = NULL;

    execvp(argv[1], arg);
}