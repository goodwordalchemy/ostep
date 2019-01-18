#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Error(char *cmd_desc){
    printf("%s failed: errno: %s\n", cmd_desc, strerror(errno));
    exit(1);
}

DIR *Open_dir(char *path){
    DIR *dp = opendir(path);
    if (dp == NULL) {
        Error("opendir");
    }
    return dp;
}

int Is_cwd_or_parent(char *filename){
    int result;
    if (strcmp(filename, ".") == 0)
        result = 1;
    else if (strcmp(filename, "..") == 0)
        result = 1;
    else
        result = 0;
    return result;
}

char *Join_path(char *base, char *head){
    int size = strlen(base) + strlen(head);
    size += 1 + 1;
    char *path = malloc(sizeof(char) * size);
    strcat(path, base);
    strcat(path, "/");
    strcat(path, head);
    return path;
}

char *Get_tab_str(int level){
    char *tab_str = malloc(sizeof(char) * (level + 1));
    int i;
    for (i = 0; i < level; i++){
        tab_str[i] = '\t';
    }
    tab_str[i+1] = '\0';
    return tab_str;
}

void Print_node(char *dir_name, int level){
    char *tab_str = Get_tab_str(level);
    printf("%s%s\n", tab_str, dir_name);
    /* free(tab_str); */
}

void Read_contents(char *dir_name, int level){
    DIR *dp = Open_dir(dir_name);
    struct dirent *d;
    while ((d = readdir(dp)) != NULL){
        char *cur_name = d->d_name;
        if (Is_cwd_or_parent(cur_name))
            continue;
        Print_node(cur_name, level);
        if (d->d_type == DT_DIR){
            char *path = Join_path(dir_name, cur_name);
            Read_contents(path, level+1);
            /* free(path); */
        }
    }
}

int main(int argc, char *argv[]) {
    char *base;
    if (argc == 2)
        base = argv[1];
    else
        base = ".";

    int level = 0;
    Read_contents(base, level);
    return 0;
}
