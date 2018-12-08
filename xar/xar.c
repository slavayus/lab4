#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *cmd = malloc(sizeof(char *));

    for (int i = 1; i < argc; ++i) {
        strcat(cmd, argv[i]);
        strcat(cmd, " ");
    }

//    char data[BUFSIZ];
//    ssize_t read_bytes = 0;
//    while ((read_bytes = read(stdin, data, BUFSIZ)) > 0) {
//        strcat(cmd, data);
//        printf("system cmd: %s\n",cmd);
//    }


    char buf[BUFSIZ];

    while (buf[strlen(buf) - 1] != '\n') {
        fgets(buf, sizeof buf, stdin);
        strcat(cmd, buf);
    }

    printf("system cmd: %s\n",cmd);

    system(cmd);
}
