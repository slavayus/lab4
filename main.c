#include <stdio.h>
#include <errno.h>
#include "copier.h"


int check_arguments(int argc, char **argv);

int copy_all_files_to_dir(int argc, char **argv);

int isDirectory(const char *path);

int main(int argc, char **argv) {
    errno = 0;

    int check_result = check_arguments(argc, argv);
    if (check_result < 0) {
        return check_result;
    }

    int result;
    if (argc == 3) {
        if (isDirectory(argv[2])) {
            result = copy_file_to_dir(argv[1], argv[2]);
        } else {
            result = copy_file_to_file(argv[1], argv[2]);
        }
    } else {
        result = copy_all_files_to_dir(argc, argv);

    }

    return result < 0 ? errno : 0;
}

int copy_all_files_to_dir(int argc, char **argv) {
    char *destination_dir = argv[argc - 1];
    for (int i = 1; i < argc - 1; ++i) {
        int result = copy_file_to_dir(argv[i], destination_dir);
        if (result < 0) {
            return errno;
        }
    }
    return 0;
}

int check_arguments(int argc, char **argv) {
    switch (argc) {
        case 1:
            printf("missing file operand\n");
            return -1;
        case 2:
            printf("missing destination file operand after '%s'\n", argv[1]);
            return -2;
        default:
            return 0;
    }
}


/*
 * slavik@slavik-K53SM:~/osp/lab4/perl$ rm -rf ../6
slavik@slavik-K53SM:~/osp/lab4/perl$ cd ..
slavik@slavik-K53SM:~/osp/lab4$ make
gcc -c -Wall -Wextra --std=gnu99 -pedantic -Werror -o main.o main.c
gcc -c -Wall -Wextra --std=gnu99 -pedantic -Werror -o copier.o copier.c
gcc -o mcp main.o copier.o
slavik@slavik-K53SM:~/osp/lab4$ mv mcp ./perl/
slavik@slavik-K53SM:~/osp/lab4$ make clean
rm -f main.o copier.o mcp
slavik@slavik-K53SM:~/osp/lab4$ cd perl/
slavik@slavik-K53SM:~/osp/lab4/perl$ ./mcp 1 2 4 ../5 ../4
slavik@slavik-K53SM:~/osp/lab4/perl$ ./mcp 1 2 3 6
copy: Is a directory
slavik@slavik-K53SM:~/osp/lab4/perl$ ./mcp 1 2 7
slavik@slavik-K53SM:~/osp/lab4/perl$ cat 7

 */