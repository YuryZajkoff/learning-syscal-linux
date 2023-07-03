/*Написание, компиляция и запуск программы с FIFO в неродственных процессах*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE    64

int main()
{
    pid_t pid, ppid;
   
    pid = getpid();
    ppid = getppid();

    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid);

    int fd_fifo; /*дескриптор FIFO*/

    char buffer[BUF_SIZE];

    /*Открываем fifo для чтения*/
    if((fd_fifo = open("/tmp/fifo0002.1", O_RDONLY )) == -1)
    {
        fprintf(stderr, "Невозможно открыть fifo\n");
        exit(1);
    }

    if(read(fd_fifo, buffer, BUF_SIZE) < 0)
    {
        close (fd_fifo);
        fprintf(stderr, "Cannot write\n");
        exit(1);
    }

    printf("%s\n", buffer);

    return 0;
}