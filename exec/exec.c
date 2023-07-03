/*
   Прогон программы с использованием системного вызова exec() - execute a file
   Для большей информации man exec
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

extern char **environ;

/*
   Первым аргументом указываем путь к исполняемому образу программы или только имя программы,
   но в этом случае поиск этой программы будет происходить исходя из переменной окружения PATH
   execlp и execvp загружают файл в командный интерпретатор shell и там исполняют то, что было внутри файла
   в этом есть необходимость, если файл не поддерживает исполнение бинарныйх.объектных файлов

   l - list
   v - vector
   e - enviroment

   argv[] - массив аргументов к выполняемому образу (как main(int argc, char** argv[]))
   envp[] - массив аргументов среды выполнения, то есть char **environ

   execl(путь, аргумент0, ..., аргументN);
   execv(путь, argv[]); - тоже как и execl, только передаем массивом, а не списком аргументов
   execle(путь, аргумент0, ..., аргументN, NULL, envp[]);
   execve(путь, argv[], envp[]);
   execlp
   execvp
*/

int main()
{

   char *echo_args[] = {"echo", "child", NULL};

   if (!fork())
   {
      // вызываем другую программу и замещаем ей, нашу (в нашем случае это программа echo)
      execve("/bin/echo", echo_args, environ);

      fprintf(stderr, "\nan error occured\n");

      return 1;
   }
   printf("parent\n");

   return 0;
}