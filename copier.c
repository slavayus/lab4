#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

#define READ_BYTE_SIZE 128

int open_source_file();

int open_destination_file(__mode_t file_mode);

int copy_file_data(int source, int destination);

int copy_file_to_file(){
    int file_descriptor_source = open_source_file();

    if (file_descriptor_source < 0) {
        perror("source");
        return errno;
    }

    struct stat file_stat;
    if (stat("1", &file_stat) < 0) {
        perror("mode");
        return errno;
    }

    int file_descriptor_destination = open_destination_file(file_stat.st_mode);

    if (file_descriptor_destination < 0) {
        perror("destination");
        return errno;
    }

    if (copy_file_data(file_descriptor_source, file_descriptor_destination) < 0) {
        perror("copy");
        return errno;
    }

    int exit = 0;
    if (close(file_descriptor_source) < 0) {
        perror("close source");
        exit = 1;
    }
    if (close(file_descriptor_destination) < 0) {
        perror("close destination");
        return errno;
    }

    return exit == 1 ? errno : 0;

}

int copy_file_data(int source, int destination) {
    char data[READ_BYTE_SIZE];
    ssize_t read_bytes = 0;
    while ((read_bytes = read(source, data, READ_BYTE_SIZE)) > 0) {
        ssize_t write_bytes = write(destination, data, read_bytes);
        if (write_bytes < 0) {
            return -1;
        }
    }
    return read_bytes < 0 ? -1 : 0;
}

int open_destination_file(__mode_t file_mode) {
    return open("2", O_WRONLY | O_CREAT, file_mode);
}

int open_source_file() {
    return open("1", O_RDONLY);
}