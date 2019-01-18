#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int c;
    int rc;
    int nLines = 5;
    char *filename;
    while ((c = getopt(argc, argv, "n:")) != -1){
        if (c == 'n') {
            nLines = atoi(optarg);
        }
    }
    if (argv[optind] == NULL){
        puts("Filename argument is missing");
        exit(1);
    }
    filename = argv[optind];

    struct stat *stat_result = malloc(sizeof(*stat_result));
    int fd;
    rc = stat(filename, stat_result);
    off_t file_size;
    if (rc == -1){
        printf("stat failed: %s\n", strerror(errno));
        exit(1);
    }
    file_size = stat_result->st_size;
    fd = open(filename, O_RDONLY);

    int nNewLines = 0;
    int step = 1;
    char read_buffer[step];
    int cur;
    for (cur = file_size - step; cur > 0; cur -= step){
        rc = lseek(fd, cur, SEEK_SET);
        if (rc == -1){
            printf("seek failed: %s\n", strerror(errno));
            exit(1);
        }
        rc = read(fd, read_buffer, step);
        if (rc == -1){
            printf("read failed: %s\n", strerror(errno));
            exit(1);
        }

        int i;
        for (i = 0; i < step; i++){
            if (read_buffer[i] == '\n'){
                nNewLines++;
            }
        }
        if (nNewLines == nLines){
            rc = lseek(fd, cur, SEEK_SET);
            if (rc == -1){
                printf("seek failed: %s\n", strerror(errno));
                exit(1);
            }
            int rem = file_size-cur;
            char output[rem];
            rc = read(fd, output, rem);
            if (rc == -1){
                printf("read failed: %s\n", strerror(errno));
                exit(1);
            }
            puts(output);
            break;
        }
    }
    puts("got to the end of the file.  just cat it");
    free(stat_result);
    return 0;
}
