/*Прогон программы с FIFO в родственных процессах*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{

    int fd_fifo; /*дескриптор FIFO*/

    pid_t pid;

    char buffer[]="Текстовая строка для fifo\n";

    /*Если файл с таким именем существует, удалим его*/

    unlink("/tmp/fifo0001.1");

    /*Создаем FIFO*/

    if((mkfifo("/tmp/fifo0001.1", S_IRWXU)) == -1)
    {
        fprintf(stderr, "Невозможно создать fifo\n");
        exit(1);
    }

    pid_t pid_f = fork();

    if (pid_f < 0)
    {
        printf("Error call function fork();\n");
        return -1;
    }
    else if (pid_f == 0)
    {
        char buf[100];
        /*Открываем fifo для чтения и записи*/
        if((fd_fifo=open("/tmp/fifo0001.1", O_RDONLY)) == -1)
        {
            fprintf(stderr, "Невозможно открыть fifo\n");
            exit(1);
        }

        if(read (fd_fifo, &buf, sizeof(buf)) < 0)
        {
            close (fd_fifo);
            fprintf (stderr, "myread: Cannot read file\n");
            exit (1);
        }
        printf("Прочитано из FIFO: %s\n",buf);
    }
    else
    {
        /*Открываем fifo для чтения и записи*/
        if((fd_fifo=open("/tmp/fifo0001.1", O_WRONLY)) == -1)
        {
            fprintf(stderr, "Невозможно открыть fifo\n");
            exit(1);
        }

        if(write(fd_fifo,buffer,strlen(buffer)) < 0)
        {
            close (fd_fifo);
            fprintf(stderr, "Cannot write\n");
            exit(1);
        }
    }

    close (fd_fifo);
    
    return 0;
}