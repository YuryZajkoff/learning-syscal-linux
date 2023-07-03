#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    int fileid = 55;
    struct stat file;
    int ppp1, ppp2;

    char name_file[] = {"for_exemple.txt"};
    char hard_link[] = {"hard_link"};
    char soft_link[] = {"soft_link"};
    
    char data[] = {"Hello, world!"};

    // Создаем и записываем данные в файл

    if ( ( fileid = creat(name_file, 0666) ) < 0 )
    {
        printf("Error creating file\n");
        exit(1);
    }

    if (write(fileid, data, sizeof(data)) != sizeof(data))
    {
        printf("Error writing file\n");
        exit(1);
    }
    
    // Создание жестких и мягких ссылок на файл

    if (link(name_file, hard_link) < 0)
    {
        printf("Error creat hard link\n");
        exit(2);
    }
    
    if (symlink(name_file, soft_link) < 0)
    {
        printf("Error creat hard link\n");
        exit(2);
    }
    // Чтение атрибутов файла

    if (fstat(fileid, &file) < 0)
    {
        printf("Error read atribut\n");
        exit(2);
    }

    printf("Атрибуты созданного файла:\n");

    printf("устройство на котором расположен файл: %ld\n",file.st_dev);

    printf("номер индексного узла для файла: %ld\n",file.st_ino);

    printf("тип файла и права доступа к нему: %d\n",file.st_mode);

    printf("счетчик числа жестких связей: %ld\n",file.st_nlink);

    printf("идентификатор пользователя владельца: %d\n",file.st_uid);

    printf("идентификатор группы владельца: %d\n",file.st_gid);

    printf("тип устройства для специальных файлов устройств: %ld\n",file.st_rdev);

    printf("размер файла в байтах: %ld\n",file.st_size);

    printf("размер блока для файловой системы: %ld\n",file.st_blksize);

    printf("число выделенных блоков: %ld\n",file.st_blocks);

    printf("время последнего доступа к файлу: %ld\n",file.st_atime);

    printf("время последней модификации файла: %ld\n",file.st_mtime);

    printf("время создания файла: %ld\n\n",file.st_ctime);


    // Удаление файла и ссылок
    fprintf(stderr, "Press <Enter> to delete files end exit...");
    getchar();
    
    if (close(fileid))
    {
        printf("Error close file\n");
        exit(2);
    }

    if (unlink(hard_link) < 0 || unlink(soft_link) < 0)
    {
        printf("Error delete link\n");
        exit(2);
    }

    if (remove(name_file) < 0)
    {
        printf("Error delete file\n");
        exit(2);
    }
    
    return 0;
}