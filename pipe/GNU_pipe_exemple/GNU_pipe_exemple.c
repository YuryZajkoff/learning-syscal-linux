/*
    Pipe - это механизм для межпроцессной связи;
    данные, записанные в канал одним процессом, могут быть прочитаны другим процессом.
    Данные обрабатываются в порядке поступления в pipe (FIFO). То есть первый зашел, первый вышел (прям как вода в трубе)
    У канала нет имени; он создан для одного использования,
    и оба конца должны быть унаследованы от одного процесса, который создал канал.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

/*
    Труба или FIFO должны быть открыты с обоих концов одновременно.
    Если вы читаете из канала или файла FIFO, в который не записываются
    какие-либо процессы (возможно, потому, что все они закрыли файл или завершили работу),
    при чтении возвращается значение end-of-file.

    Запись в канал или FIFO, у которого нет процесса чтения,
    рассматривается как условие ошибки; он генерирует сигнал SIGPIPE
    и завершается ошибкой с кодом ошибки EPIPE,
    если сигнал обработан или заблокирован.

    Ни каналы, ни специальные файлы FIFO не допускают позиционирования файлов.
    Операции чтения и записи выполняются последовательно;
    чтение с начала файла и запись в конец.

    При обычном использовании процесс создает канал непосредственно перед тем,
    как он разветвляет один или несколько дочерних процессов.
    Затем канал используется для связи либо между родительским и дочерними процессами,
    либо между двумя родственными процессами.

    Функция pipe создает канал и помещает дескрипторы файлов
    для концов чтения и записи канала (соответственно) в filedes[0] и filedes[1]

    Простой способ запомнить, что конец ввода стоит на первом месте,
    заключается в том, что файловый дескриптор 0 является стандартным вводом,
    а файловый дескриптор 1 - стандартным выводом.

    В случае успеха pipe возвращает значение 0.
    При сбое возвращается значение -1.

    Помимо прочего можно использовать вызовы popen и pclose
    (подробнее https://www.gnu.org/software/libc/manual/html_node/Pipe-to-a-Subprocess.html)
*/

/* Read characters from the pipe and echo them to stdout. */

void read_from_pipe(int file)
{
    FILE *stream;
    int c;
    stream = fdopen(file, "r");
    while ((c = fgetc(stream)) != EOF)
        putchar(c);
    fclose(stream);
}

/* Write some random text to the pipe. */

void write_to_pipe(int file)
{
    FILE *stream;
    stream = fdopen(file, "w");
    fprintf(stream, "hello, world!\n");
    fprintf(stream, "goodbye, world!\n");
    fclose(stream);
}

int main(void)
{
    pid_t pid;
    int mypipe[2];

    /* Create the pipe. */
    if (pipe(mypipe))
    {
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }

    /* Create the child process. */
    pid = fork();
    if (pid == (pid_t)0)
    {
        /* This is the child process.
           Close other end first. */
        close(mypipe[1]);
        read_from_pipe(mypipe[0]);
        return EXIT_SUCCESS;
    }
    else if (pid < (pid_t)0)
    {
        /* The fork failed. */
        fprintf(stderr, "Fork failed.\n");
        return EXIT_FAILURE;
    }
    else
    {
        /* This is the parent process.
           Close other end first. */
        close(mypipe[0]);
        write_to_pipe(mypipe[1]);
        return EXIT_SUCCESS;
    }
}