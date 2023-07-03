#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_BUF 255

int main(int argc, char** argv[])
{
    char pathname[MAX_BUF];
    DIR* curdir;
    struct dirent* curdirent;
 
    /* Get current working directory */

    if ((getcwd(pathname, MAX_BUF)) == NULL)
    {
        printf("Ошибка получения имени директории\n");
        exit(-1);
    }

    /* Open working directory in pathname*/

    if ((curdir = opendir(pathname)) == NULL)
    {
        printf("Ошибка открытия директории\n");
        exit(-1);
    }

    /* Read content dir */

    while ((curdirent = readdir(curdir)) != NULL)
    {
        printf("%s | ", curdirent->d_name);
        if (curdirent->d_type == DT_REG) printf("regular file \n");
        if (curdirent->d_type == DT_DIR) printf("directory \n");
        
    }
    
    if ((closedir(curdir)) < 0)
    {
        printf("Ошибка закрытия директории\n");
        exit(-1);
    }

    return 0;
}
