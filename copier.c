#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <libgen.h>

#define READ_BYTE_SIZE 128

int open_source_file(char *file_name);

int open_destination_file(char *destination, mode_t file_mode);

int copy_file_data(int source, int destination);

int copy_file_to_file(char *source, char *destination) {
    int file_descriptor_source = open_source_file(source);

    if (file_descriptor_source < 0) {
        perror("source");
        return errno;
    }

    struct stat file_stat;
    if (stat(source, &file_stat) < 0) {
        perror("mode");
        return errno;
    }

    int file_descriptor_destination = open_destination_file(destination, file_stat.st_mode);

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

int isDirectory(const char *path);

int open_destination_dir(char *source, char *destination, mode_t file_mode);

int copy_file_to_dir(char *source, char *destination) {
    if (isDirectory(source)) {
        printf("mcp: omitting directory '%s'\n", source);
        return 0;
    }


    int file_descriptor_source = open_source_file(source);

    if (file_descriptor_source < 0) {
        perror("source");
        return errno;
    }

    struct stat file_stat;
    if (stat(source, &file_stat) < 0) {
        perror("mode");
        return errno;
    }

    int file_descriptor_destination = open_destination_dir(source, destination, file_stat.st_mode);

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
        ssize_t write_bytes = write(destination, data, (size_t) read_bytes);
        if (write_bytes < 0) {
            return -1;
        }
    }
    return read_bytes < 0 ? -1 : 0;
}

int open_destination_file(char *destination, mode_t file_mode) {
    return open(destination, O_WRONLY | O_CREAT, file_mode);
}

int open_destination_dir(char *source, char *destination, mode_t file_mode) {
    char *source_file_name = basename(source);
    errno = 0;
    char destination_copy[strlen(destination)];
    strcpy(destination_copy, destination);
    return open(strcat(strcat(destination_copy, "/"), source_file_name), O_WRONLY | O_CREAT, file_mode);
}

int open_source_file(char *file_name) {
    return open(file_name, O_RDONLY);
}


int isDirectory(const char *path) {
    struct stat stat_buf;
    if (stat(path, &stat_buf) != 0)
        return 0;
    return S_ISDIR(stat_buf.st_mode);
}