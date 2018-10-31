#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my_pwd_func.h"

/* pwd function opens the current directory and searches through
 * the directory until it finds a directory that matches with id_node and
 * id_dev of the argument directory.
 * 
 * pwd function opens both current and parent directores, if both id_node and
 * id_dev of both directories are the same, then the function returns NULL 
 * char pointer. Else, the name of the matched file is returned. 
 * */
void my_pwd(char *cur_dir_name, char *result){
    struct stat *cur_stat = calloc(1, sizeof(struct stat)); 
    struct stat *par_stat = calloc(1, sizeof(struct stat)); 
    struct stat *temp_stat = NULL;
    char *par_dir_name = concat(cur_dir_name, "/..");
    char *found_dir_name = NULL;
    DIR *p_dir = opendir(par_dir_name); 
    struct dirent *dir = NULL;
    ret_stat_check(stat(cur_dir_name, cur_stat));
    ret_stat_check(stat(par_dir_name, cur_stat));
    if((cur_stat->st_ino != par_stat->st_ino) || 
       (cur_stat->st_dev != par_stat->st_dev)){
        temp_stat = calloc(1, sizeof(struct stat));
        while((dir = readdir(p_dir)) != NULL){
           ret_stat_check(stat(dir->d_name, temp_stat));
           if((temp_stat->st_ino == cur_stat->st_ino) &&
               temp_stat->st_dev == cur_stat->st_dev){
                
               result = concat(dir->d_name, result);
               my_pwd(par_dir_name, result);
           }
        }
    }
    else{
        free(cur_stat);
        free(par_stat);
    }
}

void ret_stat_check(int stat_ret){
    if(stat_ret == -1){
        perror("stat");
        exit(1);
    }
}

char *concat(const char *s1, const char *s2){
    char *result = calloc(strlen(s1) + strlen(s2) + 1, sizeof(char));
    if(!result){
        perror("calloc");
        exit(1);
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


