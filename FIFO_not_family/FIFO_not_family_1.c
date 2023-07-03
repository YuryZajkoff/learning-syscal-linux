/*Написание, компиляция и запуск программы с FIFO в неродственных процессах*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
    Специальный файл FIFO похож на канал, но вместо того,
    чтобы быть анонимным временным соединением, FIFO имеет имя или названия,
    подобные любому другому файлу. Процессы открывают FIFO по имени,
    чтобы взаимодействовать через него.
*/

int main()
{
    pid_t pid, ppid;
   
    pid = getpid();
    ppid = getppid();

    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid);

    int fd_fifo; /*дескриптор FIFO*/

    char buffer[]="Текстовая строка для fifo\n";

    /*Если файл с таким именем существует, удалим его*/

    unlink("/tmp/fifo0002.1");

    /*Создаем FIFO*/

    if((mkfifo("/tmp/fifo0002.1", S_IRWXU)) == -1)
    {
        fprintf(stderr, "Невозможно создать fifo\n");
        exit(1);
    }

    /*Открываем fifo для записи*/
    if((fd_fifo = open("/tmp/fifo0002.1", O_WRONLY )) == -1)
    {
        fprintf(stderr, "Невозможно открыть fifo\n");
        exit(1);
    }

    if(write(fd_fifo, buffer, strlen(buffer)) < 0)
    {
        close (fd_fifo);
        fprintf(stderr, "Cannot write\n");
        exit(1);
    }

    return 0;
}
