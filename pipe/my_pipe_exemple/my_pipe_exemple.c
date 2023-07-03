/*
	Pipe - это механизм для межпроцессной связи;
	данные, записанные в канал одним процессом, могут быть прочитаны другим процессом.
	Данные обрабатываются в порядке поступления в pipe (FIFO). То есть первый зашел, первый вышел (прям как вода в трубе)
	У канала нет имени; он создан для одного использования, 
	и оба конца должны быть унаследованы от одного процесса, который создал канал.
*/
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/*
	Труба или FIFO должны быть открыты с обоих концов одновременно. Если вы читаете из канала или файла FIFO, в который не записываются какие-либо процессы (возможно, потому, что все они закрыли файл или завершили работу), при чтении возвращается значение end-of-file.

	Запись в канал или FIFO, у которого нет процесса чтения, рассматривается как условие ошибки; он генерирует сигнал SIGPIPE и завершается ошибкой с кодом ошибки EPIPE, если сигнал обработан или заблокирован.

	Ни каналы, ни специальные файлы FIFO не допускают позиционирования файлов. Операции чтения и записи выполняются последовательно; чтение с начала файла и запись в конце.

	При обычном использовании процесс создает канал непосредственно перед тем, как он разветвляет один или несколько дочерних процессов

	Затем канал используется для связи либо между родительским, либо между дочерними процессами, либо между двумя родственными процессами.

	Функция pipe создает канал и помещает дескрипторы файлов для концов чтения и записи канала (соответственно) в filedes[0] и filedes[1]

	Простой способ запомнить, что конец ввода стоит на первом месте, заключается в том, что файловый дескриптор 0 является стандартным вводом, а файловый дескриптор 1 - стандартным выводом.

	В случае успеха pipe возвращает значение 0. При сбое возвращается значение -1.
*/

#define USAGE printf("usage : %s данные\n", argv[0]);

#define MAX 4096

void read_from_pipe(int pipe_fd)
{
	FILE *stream;
	int c;
	stream = fdopen(file, "r");
	while ((c = fgetc(stream)) != EOF)
		putchar(c);
	fclose(stream);
}

/* Write some random text to the pipe. */

void write_to_pipe(int pipe_fd)
{

	char buffer[MAX];

	strcpy(buffer, "send massage in pipe");

	size_t sz = sizeof("send massage in pipe");

	if ((write(pipe_fd, buffer, sz)) != sz)
	{
		perror(" write : ");
		exit(0);
	}

	close(pipe_fd); /*Закрываем запись*/
}

int main() 
{
	int mypipe[2];
	int fd1, i, n;

	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP; // переменная прав доступа к файлу
	int flags = O_RDONLY;

	pid_t pid;

	/*Устанавливаем трубу*/

	if (pipe(mypipe) < 0)
	{
		perror("pipe : ");
		exit(0);
	}

	/*Создаем новый процесс*/

	pid=fork();

	if(pid < 0)
	{ 
		perror("fork : ");
		exit(0);
	}
	else if(pid > 0) /*Это родитель*/ 
	{
		printf("Hey, I`m Parent!\n");

    	close(mypipe[0]); /*Закрываем чтение*/

		write_to_pipe(mypipe[1]);

		open(mypipe[0], flags, mode);
		

		if ((waitpid(pid, NULL, 0)) < 0)
		{
			perror("waitpid : ");
			exit(0);
		}

		printf("\nThis again parent\n");
		
		while (buffer[i] != 0)
		{
			buffer[i] = 0;
			i++;
		}
		n = read(mypipe[0], buffer, MAX);
		printf("I read: %s\n", buffer);
		
	}
	else /*Это потомок*/ 
	{
		// printf("\nHey, I`m Child!\n");
		// printf("My PID: %d\n", getpid());
		// printf("My PPID: %d\n", getppid());

    	//close(fd[1]); /*Закрываем запись*/

		n = read(mypipe[0], buffer, MAX);
		// printf("I read: %s", buffer);

		int i = 0;
		while (buffer[i] != 0)
		{
			buffer[i] = 0;
			i++;
		}

		strcpy(buffer,"I am fine");

		size_t sz = sizeof("I am fine");

		if ((write(mypipe[1], buffer, sz)) != sz)
		{
			perror(" write : ");
			exit(0);
		}
		// printf("I write: %s\n", buffer);



		
	}
	exit(0);
}

