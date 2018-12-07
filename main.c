#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int open_source_file();

int open_destination_file();

int main() {
    errno = 0;

    int file_descriptor_source = open_source_file();

    if (file_descriptor_source < 0) {
        perror("source");
        return errno;
    }

    int file_descriptor_destination = open_destination_file();

    if (file_descriptor_destination < 0) {
        perror("destination");
        return errno;
    }

    printf("file no=%i\n", file_descriptor_source);
    printf("file no=%i\n", file_descriptor_destination);

    return 0;
}

int open_destination_file() {
    return open("2", O_WRONLY | O_CREAT, S_IWUSR);
}

int open_source_file() {
    return open("1", O_RDONLY);
}