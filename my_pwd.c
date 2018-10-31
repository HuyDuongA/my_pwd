#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_pwd_func.h"

/* The main funtion gets stat of the current directory and call pwd for 
 * current directory.
 * */
int main(){
    int stat_num = 0;
    char *pwd_str = "";
    struct stat *buf = calloc(1, sizeof(struct stat));
    stat_num = stat(".", buf);
    if(stat_num == -1){
        perror("stat");
        exit(1);
    }
    my_pwd(".", pwd_str);  
    return 0;
}


