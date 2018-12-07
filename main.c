#include <stdio.h>
#include <errno.h>
#include "copier.h"


int check_arguments(int argc, char **argv);

int copy_all_files_to_dir(int argc, char **argv);

int main(int argc, char **argv) {
    errno = 0;

    int check_result = check_arguments(argc, argv);
    if (check_result < 0) {
        return check_result;
    }

    int result = copy_all_files_to_dir(argc, argv);
    return result < 0 ? errno : 0;
}

int copy_all_files_to_dir(int argc, char **argv) {
    char *destination_dir = argv[argc - 1];
    for (int i = 1; i < argc - 1; ++i) {
        int result = copy_file_to_file(argv[i], destination_dir);
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
