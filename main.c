#include <stdio.h>
#include <errno.h>
#include "copier.h"


int check_arguments(int argc, char **argv);

int main(int argc, char **argv) {
    errno = 0;

    int check_result = check_arguments(argc, argv);
    if (check_result < 0) {
        return check_result;
    }

    switch (argc) {
        case 3: {
            int result = copy_file_to_file();
            return result < 0 ? errno : 0;
        }

        default:break;
    }

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
            break;
    }
}
