#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2){
        puts("What file do you want to stat?!");
        exit(1);
    }
    char* filepath = argv[1];
    struct stat *stat_result;

    int rc = stat(filepath, stat_result);
    if (rc == -1){
        puts("Stat failed");
        exit(1);
    }
    printf("file size: %lld\n", stat_result->st_size);
    printf("num blocks: %lld\n", stat_result->st_blocks);
    printf("number of hard links: %d\n", stat_result->st_nlink);
    printf("inode: %d\n", stat_result->st_dev);
}
