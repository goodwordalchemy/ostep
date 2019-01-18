#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int c;
    int lflag = 0;

    while ((c = getopt(argc, argv, "l")) != -1){
        if (c == 'l')
            lflag = 1;
    }
    int index;
    index = optind;
    char *path;
    if (index != argc){
        path = argv[index];
    }
    else {
        path = ".";
    }

    DIR *dp = opendir(path);
    if (dp == NULL) {
        printf("opendir failed: errno: %s\n", strerror(errno));
        exit(1);
    }
    struct dirent *d;
    struct stat *stat_result = malloc(sizeof(*stat_result));
    char *filepath;
    int rc;
    while ((d = readdir(dp)) != NULL){
        if (lflag==0){
            printf("%s\n", d->d_name);
        }
        else {
            filepath = d->d_name;
            printf("filepath: %s\n", filepath);
            rc = stat(filepath, stat_result);
            if (rc == -1){
                printf("stat failed: errno: %s\n", strerror(errno));
                exit(1);
            }
            printf("name: %s, owner: %d, group %d, permissions: %d\n",
                   d->d_name, stat_result->st_uid, 
                   stat_result->st_gid, stat_result->st_mode);
        }
    }
    free(stat_result);
        
}
