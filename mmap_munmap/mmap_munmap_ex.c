/*

*/
#include <unistd.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
    Подробнее о системных вызовах в man
*/
int main(void)
{
    int fd;
    size_t length; /* Длина отображаемой части файла */

    /*
        Элемент хранения данных в файле
    */
    struct A
    {
        int id;
        float otherData;
    } *ptr, *tmpptr;

    /*
        сначала выполняется отображение в дисковое пространство, а уже затем из дискового пространства в адресное
        с помощью системного вызова open()
    */
    fd = open("mapped.dat", O_RDWR | O_CREAT, 0666);
    if (fd == -1)
    {
        printf("File open failed!\n");
        exit(1);
    }

    length = 5000 * sizeof(struct A);

    /* 
        Устанавливаем длину обычного файла с именем path или файловым дескриптором fd в length байт
    */
    ftruncate(fd, length);

    /*
        mmap - это memory mapped!
        Системный вызов, позволяющий выполнить отображение файла или устройства на память.
        Отображение файла целиком или частично из дискового пространства в адресное пространство процесса.
        void * mmap(void *start, size_t length, int prot , int flags, int fd, off_t offset);
        Функция mmap отражает length байтов, начиная со смещения offset файла (или другого объекта),
        определенного файловым описателем fd, в память, начиная с адреса start.
        Настоящее местоположение отраженных данных возвращается самой функцией mmap, и никогда не бывает равным 0.
        Подробнее в man
    */
    ptr = (struct A *)mmap(NULL, length, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

    close(fd);

    if (ptr == MAP_FAILED)
    {
        printf("Mapping failed!\n");
        exit(2);
    }

    tmpptr = ptr;

    srand(6);
    /*
        Производим некоторые действия над отображенной областью памяти
    */
    for (int i = 1; i <= 5000; i++)
    {
        tmpptr->id = i;
        tmpptr->otherData = rand() % 5000;
        tmpptr++;
    }

    /*
        munmap - 'это unmap memory!
        Системный вызов munmap служит для прекращения отображения memory mapped
        файла в адресное пространство вычислительной системы.
        Если при системном вызове mmap() было задано значение параметра flags,
        равное MAP_SHARED, и в отображении файла была разрешена операция записи
        (в параметре prot использовалось значение PROT_WRITE ), то munmap
        синхронизирует содержимое отображения с содержимым файла во вторичной памяти.
        После его выполнения области памяти, использовавшиеся для отображения файла,
        становятся недоступны текущему процессу.
    */
    munmap((void *)ptr, length);


    /*
        Делаем второй заход отображения файла и читаем его содержимое
    */
    if ((fd = open("mapped.dat", O_RDWR | O_CREAT, 0666)) == -1)
    {
        printf("File open failed!\n");
        exit(1);
    }

    ptr = (struct A *)mmap(NULL, length, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

    close(fd);
    if (ptr == MAP_FAILED)
    {
        printf("Mapping failed!\n");
        exit(2);
    }

    tmpptr = ptr;
    for (int i = 1; i <= 5000; i++)
    {
        printf("%d\t", tmpptr->id);
        printf("%f\n", tmpptr->otherData);
        tmpptr++;
    }

    munmap((void *)ptr, length);

    if (remove("mapped.dat") < 0)
    {
        printf("Error delete file\n");
        exit(2);
    }

    return 0;
}